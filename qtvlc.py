#! /usr/bin/python

#
# Qt example for VLC Python bindings
# Copyright (C) 2009-2010 the VideoLAN team
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
#

import sys
import os.path
import vlc
import serial
import threading
from PyQt4 import QtGui, QtCore

class myDockWidget(QtGui.QDockWidget):
    
    def keyPressEvent(self, event):
        parent = self.parentWidget()
        parent.keyPressEvent(event)

    def mousePressEvent(self, event):
        if event.button() == QtCore.Qt.RightButton :
            parent = self.parentWidget()
            parent.toggleFullscreen()

    def closeEvent(self, event):
        try :
            global wannastop
            wannastop = True
            self.hide()
            sys.exit()
        except ValueError:
            print(ValueError)
            pass

class myListWidget(QtGui.QListWidget):

    def doubleClicked(self,item):
        QtGui.QMessageBox.information(self, "ListWidget", "You clicked: "+item.text())
      
    def keyPressEvent(self, event):
        parent = self.parentWidget()
        parent.keyPressEvent(event)

    #def mousePressEvent(self, event):
    #    parent = self.parentWidget()
    #    parent.mousePressEvent(event)

class Player(QtGui.QMainWindow):
    """A simple Media Player using VLC and Qt
    """
    def __init__(self, master=None):
        QtGui.QMainWindow.__init__(self, master)
        self.setWindowTitle("Media Player")

        # creating a basic vlc instance
        self.instance = vlc.Instance()
        # creating an empty vlc media player
        self.mediaplayer = self.instance.media_player_new()

        self.createUI()
        self.isPaused = False
        
        self.setWindowFlags(QtCore.Qt.Window | QtCore.Qt.FramelessWindowHint)
                    
    def closeEvent(self, event):
        try :
            global wannastop
            wannastop = True
            sys.exit()
        except :
            pass
    
    def clearLayout(self, layout):
        layouts = []
        for i in reversed(range(layout.count())): 
            if (type(layout.itemAt(i)) == QtGui.QWidgetItem):
                layout.itemAt(i).widget().setParent(None) 

    def createLayout(self) :
        self.positionslider = QtGui.QSlider(QtCore.Qt.Horizontal, self)
        self.positionslider.setToolTip("Position")
        self.positionslider.setMaximum(1000)
        self.connect(self.positionslider,
             QtCore.SIGNAL("sliderMoved(int)"), self.setPosition)
        
        self.hbuttonbox = QtGui.QHBoxLayout()                        
        self.playbutton = QtGui.QPushButton("Play")                
        if self.mediaplayer.is_playing():
            self.playbutton.setText("Pause")
        self.hbuttonbox.addWidget(self.playbutton)
        self.connect(self.playbutton, QtCore.SIGNAL("clicked()"),
                     self.PlayPause)

        self.stopbutton = QtGui.QPushButton("Stop")
        self.hbuttonbox.addWidget(self.stopbutton)
        self.connect(self.stopbutton, QtCore.SIGNAL("clicked()"),
                     self.Stop)

        self.hbuttonbox.addStretch(1)
        self.volumeslider = QtGui.QSlider(QtCore.Qt.Horizontal, self)
        self.volumeslider.setMaximum(100)
        self.volumeslider.setValue(self.mediaplayer.audio_get_volume())
        self.volumeslider.setToolTip("Volume")
        self.hbuttonbox.addWidget(self.volumeslider)
        self.connect(self.volumeslider,
                     QtCore.SIGNAL("valueChanged(int)"),
                     self.setVolume)                     

        self.vboxlayout.addWidget(self.positionslider)
        self.vboxlayout.addLayout(self.hbuttonbox)
        
        self.listWidget = myListWidget()
        self.listWidget.addItem("Item 1"); 
        self.listWidget.addItem("Item 2");
        self.listWidget.addItem("Item 3");
        self.listWidget.addItem("Item 4"); 

        self.spRight = QtGui.QSizePolicy(QtGui.QSizePolicy.Preferred, QtGui.QSizePolicy.Preferred)        
        self.spRight.setHorizontalStretch(0)
        self.listWidget.setSizePolicy(self.spRight)  
        self.listWidget.itemDoubleClicked.connect(self.listWidget.doubleClicked)        
        self.myhboxlayout.addWidget(self.listWidget)
        
    def keyPressEvent(self, event):
        key = event.key()
        if key == QtCore.Qt.Key_F:
            self.toggleFullscreen()

    #def mousePressEvent(self, event):
    #    if event.button() == QtCore.Qt.RightButton :
    #        self.toggleFullscreen()
                
    def toggleFullscreen(self):
        self.setWindowState(self.windowState() ^ QtCore.Qt.WindowFullScreen)
        if self.windowState() & QtCore.Qt.WindowFullScreen :
            self.clearLayout(self.hbuttonbox)  
            self.listWidget.setParent(None)                
            self.positionslider.setParent(None)
        else :
            self.createLayout()

    def createUI(self):
        """Set up the user interface, signals & slots
        """
        self.widget = QtGui.QWidget(self)
        self.setCentralWidget(self.widget)

        # In this widget, the video will be drawn
        if sys.platform == "darwin": # for MacOS
            self.videoframe = QtGui.QMacCocoaViewContainer(0)
        else:
            self.videoframe = QtGui.QFrame()
        self.palette = self.videoframe.palette()
        self.palette.setColor (QtGui.QPalette.Window,
                               QtGui.QColor(0,0,0))
        self.videoframe.setPalette(self.palette)
        self.videoframe.setAutoFillBackground(True)
        

        self.myhboxlayout = QtGui.QHBoxLayout()
        self.myhboxlayout.setSpacing(0)
        self.myhboxlayout.setContentsMargins(0,0,0,0);
        
        self.vboxlayout = QtGui.QVBoxLayout()
        self.vboxlayout.setSpacing(0)
        self.vboxlayout.setContentsMargins(0,0,0,0);

        self.vboxlayout.addWidget(self.videoframe)
        
        self.myhboxlayout.addLayout(self.vboxlayout)        
        self.widget.setLayout(self.myhboxlayout)
        
        self.createLayout()

        self.dockWidget = myDockWidget(self, QtCore.Qt.Window |  QtCore.Qt.WindowStaysOnTopHint | QtCore.Qt.FramelessWindowHint)
        #self.dockWidget.setFloating(True)
        self.dockWidget.setGeometry(150,150,640,480)
        #self.dockWidget.setFeatures( QtGui.QDockWidget.NoDockWidgetFeatures )
        self.dockWidget.setAllowedAreas( QtCore.Qt.NoDockWidgetArea );
        self.dockWidget.show()
        self.dockWidget.setWindowOpacity(0.5);

        self.timer = QtCore.QTimer(self)
        self.timer.setInterval(200)
        self.connect(self.timer, QtCore.SIGNAL("timeout()"),
                     self.updateUI)

        self.timercounter = QtCore.QTimer(self)
        self.timercounter.setInterval(1000)
        self.connect(self.timercounter, QtCore.SIGNAL("timeout()"),
                     self.CycleHandler)

    def CycleHandler(self):
        global counter
        state = self.mediaplayer.get_state()
        if state != vlc.State.Opening :     
            counter = counter - 1      
            if counter <= 0 and not self.isPaused:
                self.playbutton.setText("Play")
                self.mediaplayer.pause()
                self.isPaused = True
            elif counter > 0 and self.isPaused:
                self.mediaplayer.play()
                self.playbutton.setText("Pause")
                self.isPaused = False

    def PlayPause(self):
        """Toggle play/pause status
        """                
        if self.mediaplayer.is_playing():
            self.mediaplayer.pause()
            self.playbutton.setText("Play")
            self.isPaused = True
        else:
            if self.mediaplayer.play() == -1:
                self.OpenFile()
                return
            self.mediaplayer.play()
            self.playbutton.setText("Pause")
            self.timer.start()
            self.timercounter.start()
            self.isPaused = False

    def Stop(self):
        """Stop player
        """
        self.mediaplayer.stop()
        self.playbutton.setText("Play")
        self.timercounter.stop()

    def OpenFile(self, filename=None):
        """Open a media file in a MediaPlayer
        """
        if filename is None:
            filename = QtGui.QFileDialog.getOpenFileName(self, "Open File", os.path.expanduser('~'))
        if not filename:
            return

        # create the media
        if sys.version < '3':
            filename = unicode(filename)
        self.media = self.instance.media_new(filename)
        # put the media in the media player
        self.mediaplayer.set_media(self.media)

        # parse the metadata of the file
        self.media.parse()
        # set the title of the track as window title
        self.setWindowTitle(self.media.get_meta(0))

        # the media player has to be 'connected' to the QFrame
        # (otherwise a video would be displayed in it's own window)
        # this is platform specific!
        # you have to give the id of the QFrame (or similar object) to
        # vlc, different platforms have different functions for this
        if sys.platform.startswith('linux'): # for Linux using the X Server
            self.mediaplayer.set_xwindow(self.videoframe.winId())
        elif sys.platform == "win32": # for Windows
            self.mediaplayer.set_hwnd(self.videoframe.winId())
        elif sys.platform == "darwin": # for MacOS
            self.mediaplayer.set_nsobject(self.videoframe.winId())
        self.PlayPause()

    def setVolume(self, Volume):
        """Set the volume
        """
        self.mediaplayer.audio_set_volume(Volume)

    def setPosition(self, position):
        """Set the position
        """
        # setting the position to where the slider was dragged
        self.mediaplayer.set_position(position / 1000.0)
        # the vlc MediaPlayer needs a float value between 0 and 1, Qt
        # uses integer variables, so you need a factor; the higher the
        # factor, the more precise are the results
        # (1000 should be enough)

    def updateUI(self):
        """updates the user interface"""
        # setting the slider to the desired position
        self.positionslider.setValue(self.mediaplayer.get_position() * 1000)
        state = self.mediaplayer.get_state()
        if not self.mediaplayer.is_playing() and state != vlc.State.Opening :
            self.timer.stop()
            if not self.isPaused:
                # after the video finished, the play button stills shows
                # "Pause", not the desired behavior of a media player
                # this will fix it
                self.Stop()

connected = False
port = 'COM5'
baud = 115200
#serial_port = serial.Serial(port, baud, timeout=0)
wannastop = False
counter = 0

def handle_data(data):
    if data == "1" :
        global counter
        counter = 3

def read_from_port(ser):
    global connected
    while not connected:
        #serin = ser.read()
        connected = True

        while True and not wannastop:
           reading = ser.readline().decode().strip('\r\n')
           handle_data(reading)

if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    player = Player()
    player.show()
    player.showMaximized()
    #player.resize(640,480)
    global playerPtr
    playerPtr = player
    #thread = threading.Thread(target=read_from_port, args=(serial_port,))
    thread.start()
    if sys.argv[1:]:
        player.OpenFile(sys.argv[1])
    sys.exit(app.exec_())
