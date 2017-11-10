#Blank Window
import sys
from PyQt4 import QtGui
def main():
	app = QtGui.QApplication(sys.argv)
	w = QtGui.QWidget()
	w.resize(640, 480)
	w.move(350, 120)
	w.setWindowTitle('Simple')
	w.show()
	return app.exec_()
	# sys.exit(app.exec_())
if __name__ == '__main__':
    main()