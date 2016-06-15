/**
 * @author Cameron Kumar
 * @version 1.0 
 * @date 15 June 2016
 * @brief simple calculator developed using Qt.
 *
 * Application that creates a simple calculator using Qt. Can do addition, 
 * subtraction, multiplication and division operations.
 */
 
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>

/**
 * Class defining a number button on a calculator. Inherits from QPushButton.
 */
class numButton: public QPushButton {

  /**
   * holds integer value displayed on the button
   */
  int val; 
  
  public:
  /**
   * class constructor, sets val to specified integer and sets text
   *  
   * @param value of button 
   */
  numButton(int v) { val = v; text = v;}

};
 

/**
 * Creates the "screen" of the calculator where calculations are displayed to
 * provide some user feedback. This is made as a QTextEdit widget. Layout passed
 * to this function by reference.
 *
 * @param layout layout of the calculator for the widget to be created in.
 */
void createScreen(QGridLayout layout) {
	
  QTextEdit *screen = new QTextEdit("0"); // initialising text edit
  screen.setReadOnly(1); // setting read only
  // now adding widget to layout, spans 3 columns
  layout.addWidget(screen, 0, 0, 1, 3, Qt::AlignHCenter);
	
}

/**
 * Slot to handle a number button being pressed.
 *
 * @param val value of pressed number button
 */
void numPress(int Val) {

	

}

/**
 * Creates each of the number buttons 0-9 in layout of a calculator.
 *
 * @param layout layout of the calculator for the widget to be created in.
 */
void createNumberButtons(QGridLayout layout) {

  // create 1-9 number buttons using 2 for loops 
  for(int i = 1; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      
      // creating the button
      numButton but(i+(j*3));
      // add button into layout
      layout-> addWidget(but, i+1, j, Qt::AlignHCenter);
      
      // connection made to handle button presses using signal mapper
      QSignalMapper *numPress = new QSignalMapper(this); // create mapper
      connect(but, SIGNAL(pressed()), num, SLOT(map()));
      num->setMapping(but, val); // pass val to slot as an int
      connect(num, SIGNAL(mapped(int)), this, SLOT(numPress(int)));
    }
  }

}

/**
 * Main function. Sets up the Qt context, creates the layout and window for 
 * calculator. Executes the application.
 *  
 * @param argc number of command line arguments
 * @param argv command line arguments
 * @return exit status, normal 0
 */
int main(int argc, char **argv) {

  QApplication app(argc, argv); // start qt context
  
  // creating qt layout to hold widgets
  QGridLayout *calcLayout = new QGridLayout;
  
  createScreen(calcLayout); // create widget acting as calculator screen
  createNumberButtons(); // create number button widgets
  createOperatorButtons(); // create operator button widgets
  
  // create the window to display calculator and set size
  QWidget window;
  window.setFixedSize(90, 200);

}
