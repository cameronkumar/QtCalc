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
#include <QSignalMapper>

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
  numButton(int v);
  
  /**
   * getter function. returns val.
   *
   * @return integer value of val
   */
  int getVal() { return val; }

};

/**
 * class constructor, sets val to specified integer and sets text
 *  
 * @param value of button 
 */
numButton::numButton(int v) {

	val = v; // set value
	setText(QString::number(v)); // set button text
	
}

/**
 * Class defining the calculator's screen. Contains slots to handle button presses.
 */
class calcScreen: public QTextEdit {

  /**
   * holds the current value of calculator input, displayed on screen
   */
  double val;
  
  /**
   * holds last answer value for calculations
   */
  double ans;
 
  public:
  /**
   * class constructor, initialises value to 0
   */
  calcScreen() { val = 0.0; setReadOnly(1); }
  
  private slots:
  /**
   * slot to handle presses of calculator number buttons
   *
   * @param v value of number button pressed
   */
  void numPress(int v);

};

/**
  * slot to handle presses of calculator number buttons
  *
  * @param v value of number button pressed
  */
void calcScreen::numPress(int v) {

  val = val*10.0; // multiply currently displayed value
  val += v; // add on new input;

}
 

/**
 * Creates the "screen" of the calculator where calculations are displayed to
 * provide some user feedback. This is made as a QTextEdit widget. Layout passed
 * to this function by reference.
 *
 * @param layout layout of the calculator for the widget to be created in.
 */
void createScreen(QGridLayout *layout) {
	
  // initialising screen
  calcScreen *screen = new calcScreen;
  // now adding widget to layout, spans 3 columns
  layout->addWidget(screen, 0, 0, 1, 3, Qt::AlignHCenter);
	
}

/**
 * Creates each of the number buttons 0-9 in layout of a calculator.
 *
 * @param layout layout of the calculator for the widget to be created in.
 */
void createNumberButtons(QGridLayout *layout) {

  // create 1-9 number buttons using 2 for loops 
  for(int i = 1; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      
      // creating the button
      numButton *but = new numButton(i+(j*3));
      // add button into layout
      layout->addWidget(but, i+1, j, Qt::AlignHCenter);
      
      // connection made to handle button presses using signal mapper
      QSignalMapper *num = new QSignalMapper(); // create mapper
      QObject::connect(but, SIGNAL(pressed()), num, SLOT(map()));
      num->setMapping(but, (i+(j*3))); // pass val to slot as an int
      QObject::connect(num, SIGNAL(mapped(int)), calcScreen, SLOT(numPress(int)));
    }
  }
  
  // create the 0 button
  numButton *zero = new numButton(0);
  // add it to the layout, spans 2 columns
  layout->addWidget(zero, 5, 0, 1, 2, Qt::AlignHCenter);
  
  // connect with signal slot connection using signal mapper
  QSignalMapper *num = new QSignalMapper(); // create mapper
  QObject::connect(zero, SIGNAL(pressed()), num, SLOT(map()));
  num->setMapping(zero, 0); // pass val to slot as an int
  QObject::connect(num, SIGNAL(mapped(int)), calcScreen, SLOT(numPress(int)));
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
