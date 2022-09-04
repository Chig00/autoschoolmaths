#include <iostream>
#include "sdlandnet.hpp"

// Constants
//{
// The current version.
constexpr int VERSION[System::VERSION_LENGTH] = {2, 0, 0, 0};

// The number of different types of question.
constexpr int QUESTION_TYPES = 4;

// The number of different types of question outcome.
constexpr int OUTCOME_TYPES = 3;

// Returned by Question::question() if the program should terminate.
constexpr int TERMINATE = -1;

// Returned by Question::question() if the quiz wasn't finished.
constexpr int QUIT = 1;

// The default test configuration.
//{
constexpr int SUM_MIN = 0;
constexpr int SUM_MAX = 20;
constexpr int PRODUCT_MIN = 0;
constexpr int PRODUCT_MAX = 12;
constexpr int SET_COUNT = 3;
constexpr int TIME_LIMIT = 20;
//}

// Test configuration constants.
//{
constexpr int SUM_DIGITS = 3;
constexpr int PRODUCT_DIGITS = 2;
constexpr int SET_DIGITS = 2;
constexpr int TIME_DIGITS = 3;
constexpr int SUM_RANGE[] = {-999, 999};
constexpr int PRODUCT_RANGE[] = {-99, 99};
constexpr int SET_RANGE[] = {1, 99};
constexpr int TIME_RANGE[] = {0, 999};
//}

// The keybindings values.
//{
constexpr int QUIT_KEY = Events::ESCAPE;
constexpr int SUBMIT_KEY = Events::ENTER;
constexpr int BACK_KEY = Events::BACKSPACE;
constexpr int MINUS_KEY = Events::MINUS;
constexpr int PREVIOUS_KEY = Events::LEFT;
constexpr int NEXT_KEY = Events::RIGHT;
constexpr const int* NUMBER_KEYS = Events::NUMBERS;
//}

// The maximum length of an attempt at an answer.
constexpr int MAX_ATTEMPT = 5;

// Positions and dimensions.
//{
// Position and dimensions of the title.
//{
constexpr double TITLE_WIDTH = 0.75;
constexpr double TITLE_HEIGHT = 0.4;
constexpr double TITLE_X = 0.5;
constexpr double TITLE_Y = 0.25;
//}

// Position and dimensions of the copyright button.
//{
constexpr double COPYRIGHT_WIDTH = 0.3;
constexpr double COPYRIGHT_HEIGHT = 0.0875;
constexpr double COPYRIGHT_X = 0.1625;
constexpr double COPYRIGHT_Y = 0.9375;
//}

// Position and dimensions of the start button.
//{
constexpr double START_WIDTH = 0.2;
constexpr double START_HEIGHT = 0.125;
constexpr double START_X = 0.5;
constexpr double START_Y = 0.625;
//}

// Position and dimensions of the info button.
//{
constexpr double INFO_WIDTH = START_WIDTH;
constexpr double INFO_HEIGHT = START_HEIGHT;
constexpr double INFO_X = START_X;
constexpr double INFO_Y = 0.825;
//}

// Position and dimensions of the quit button.
//{
constexpr double QUIT_WIDTH = 0.125;
constexpr double QUIT_HEIGHT = 0.0875;
constexpr double QUIT_X = 0.925;
constexpr double QUIT_Y = 0.95;
//}

// Position and dimensions of the info screen.
//{
constexpr double INFO_SCREEN_WIDTH = 0.9;
constexpr double INFO_SCREEN_HEIGHT = 0.75;
constexpr double INFO_SCREEN_X = 0.5;
constexpr double INFO_SCREEN_Y = 0.45;
//}

// Position and dimensions of the sum range prompt.
//{
constexpr double SUM_WIDTH = 0.4;
constexpr double SUM_HEIGHT = 0.1375;
constexpr double SUM_X = 0.225;
constexpr double SUM_Y = 0.1;
//}

// Position and dimensions of the product range prompt.
//{
constexpr double PRODUCT_WIDTH = SUM_WIDTH;
constexpr double PRODUCT_HEIGHT = SUM_HEIGHT;
constexpr double PRODUCT_X = SUM_X;
constexpr double PRODUCT_Y = 0.325;
//}

// Position and dimensions of the question set count prompt.
//{
constexpr double SET_WIDTH = PRODUCT_WIDTH;
constexpr double SET_HEIGHT = PRODUCT_HEIGHT;
constexpr double SET_X = PRODUCT_X;
constexpr double SET_Y = 0.55;
//}

// Position and dimensions of the question time prompt.
//{
constexpr double TIME_WIDTH = SET_WIDTH;
constexpr double TIME_HEIGHT = SET_HEIGHT;
constexpr double TIME_X = SET_X;
constexpr double TIME_Y = 0.775;
//}

// Position and dimensions of the to button.
//{
constexpr double TO_WIDTH = 0.05;
constexpr double TO_HEIGHT = 0.075;
constexpr double TO_X[] = {0.7, 0.7};
constexpr double TO_Y[] = {SUM_Y, PRODUCT_Y};
//}

// Position and dimensions of the back button.
//{
constexpr double BACK_WIDTH = QUIT_WIDTH;
constexpr double BACK_HEIGHT = QUIT_HEIGHT;
constexpr double BACK_X = 1 - QUIT_X;
constexpr double BACK_Y = QUIT_Y;
//}

// Position and dimensions of the begin button.
//{
constexpr double BEGIN_WIDTH = BACK_WIDTH;
constexpr double BEGIN_HEIGHT = BACK_HEIGHT;
constexpr double BEGIN_X = 1 - BACK_X;
constexpr double BEGIN_Y = BACK_Y;
//}

// Position and dimensions of the up arrow button.
//{
constexpr double UP_WIDTH = 0.04;
constexpr double UP_HEIGHT = 0.03;
//}

// Position and dimensions of the down arrow button.
//{
constexpr double DOWN_WIDTH = UP_WIDTH;
constexpr double DOWN_HEIGHT = UP_HEIGHT;
//}

// Position and dimensions of the minimum sum value.
//{
constexpr double SUM_MIN_WIDTH = DOWN_WIDTH;
constexpr double SUM_MIN_HEIGHT = TO_HEIGHT;
constexpr double SUM_MIN_X = 0.55;
constexpr double SUM_MIN_Y = TO_Y[0];
//}

// Position and dimensions of the maximum sum value.
//{
constexpr double SUM_MAX_WIDTH = SUM_MIN_WIDTH;
constexpr double SUM_MAX_HEIGHT = SUM_MIN_HEIGHT;
constexpr double SUM_MAX_X = 2 * TO_X[0] - SUM_MIN_X;
constexpr double SUM_MAX_Y = SUM_MIN_Y;
//}

// Position and dimensions of the minimum product value.
//{
constexpr double PRODUCT_MIN_WIDTH = SUM_MAX_WIDTH;
constexpr double PRODUCT_MIN_HEIGHT = SUM_MAX_HEIGHT;
constexpr double PRODUCT_MIN_X = SUM_MIN_X;
constexpr double PRODUCT_MIN_Y = TO_Y[1];
//}

// Position and dimensions of the maximum product value.
//{
constexpr double PRODUCT_MAX_WIDTH = PRODUCT_MIN_WIDTH;
constexpr double PRODUCT_MAX_HEIGHT = PRODUCT_MIN_HEIGHT;
constexpr double PRODUCT_MAX_X = 2 * TO_X[1] - PRODUCT_MIN_X;
constexpr double PRODUCT_MAX_Y = PRODUCT_MIN_Y;
//}

// Position and dimensions of the question set count value.
//{
constexpr double SET_COUNT_WIDTH = PRODUCT_MAX_WIDTH;
constexpr double SET_COUNT_HEIGHT = PRODUCT_MAX_HEIGHT;
constexpr double SET_COUNT_X = TO_X[1];
constexpr double SET_COUNT_Y = SET_Y;
//}

// Position and dimensions of the time limit value.
//{
constexpr double TIME_LIMIT_WIDTH = SET_COUNT_WIDTH;
constexpr double TIME_LIMIT_HEIGHT = SET_COUNT_HEIGHT;
constexpr double TIME_LIMIT_X = SET_COUNT_X;
constexpr double TIME_LIMIT_Y = TIME_Y;
//}

// Position and dimensions of the operands.
//{
constexpr double OPERAND_WIDTH = 0.05;
constexpr double OPERAND_HEIGHT = 0.125;
constexpr double OPERAND_X[] = {0.1125, 0.45};
constexpr double OPERAND_Y = 0.3;
//}

// Position and dimensions of the operators.
//{
constexpr double OPERATOR_WIDTH = 0.075;
constexpr double OPERATOR_HEIGHT = 0.0875;
constexpr double OPERATOR_X = (OPERAND_X[0] + OPERAND_X[1]) / 2;
constexpr double OPERATOR_Y = OPERAND_Y;
//}

// Position of the equals sign.
//{
constexpr double EQUALS_X = 2 * OPERAND_X[1] - OPERATOR_X;
constexpr double EQUALS_Y = OPERATOR_Y;
//}

// Position and dimensions of the attempted answer.
//{
constexpr double ATTEMPT_WIDTH = OPERAND_WIDTH;
constexpr double ATTEMPT_HEIGHT = OPERAND_HEIGHT;
constexpr double ATTEMPT_X = 2 * EQUALS_X - OPERAND_X[1];
constexpr double ATTEMPT_Y = OPERAND_Y;
//}

// Position and dimensions of the timer.
//{
constexpr double TIMER_WIDTH = 0.05;
constexpr double TIMER_HEIGHT = 0.5;
constexpr double TIMER_X = 0.95;
constexpr double TIMER_Y = 0.3;
//}

// Position and dimensions of the results.
//{
constexpr double RESULTS_WIDTH = 0.3;
constexpr double RESULTS_HEIGHT = TIME_HEIGHT;
constexpr double RESULTS_X = 0.1625;
constexpr double RESULTS_Y = 0.1;
//}

// Position and dimensions of the slash.
//{
constexpr double SLASH_WIDTH = 0.0375;
constexpr double SLASH_HEIGHT = RESULTS_HEIGHT;
constexpr double SLASH_X = 0.5;
constexpr double SLASH_Y = RESULTS_Y;
//}

// Position and dimensions of the percent sign.
//{
constexpr double PERCENT_WIDTH = 0.075;
constexpr double PERCENT_HEIGHT = SLASH_HEIGHT;
constexpr double PERCENT_X = 0.925;
constexpr double PERCENT_Y = SLASH_Y;
//}

// Positions and dimensions of the left arrow button.
//{
constexpr double LEFT_WIDTH = 0.025;
constexpr double LEFT_HEIGHT = 0.1;
constexpr double LEFT_X = 0.025;
constexpr double LEFT_Y = 0.5;
//}

// Positions and dimensions of the right arrow button.
//{
constexpr double RIGHT_WIDTH = LEFT_WIDTH;
constexpr double RIGHT_HEIGHT = LEFT_HEIGHT;
constexpr double RIGHT_X = 1 - LEFT_X;
constexpr double RIGHT_Y = LEFT_Y;
//}

// Positions and dimensions of the score.
//{
constexpr double SCORE_WIDTH = 0.0375;
constexpr double SCORE_HEIGHT = PERCENT_HEIGHT;
constexpr double SCORE_X = 0.4;
constexpr double SCORE_Y = PERCENT_Y;
//}

// Positions and dimensions of the total.
//{
constexpr double TOTAL_WIDTH = SCORE_WIDTH;
constexpr double TOTAL_HEIGHT = SCORE_HEIGHT;
constexpr double TOTAL_X = 2 * SLASH_X - SCORE_X;
constexpr double TOTAL_Y = SCORE_Y;
//}

// Position and dimensions of the percentage.
//{
constexpr double PERCENTAGE_WIDTH = TOTAL_WIDTH;
constexpr double PERCENTAGE_HEIGHT = TOTAL_HEIGHT;
constexpr double PERCENTAGE_X = 0.8;
constexpr double PERCENTAGE_Y = TOTAL_Y;
//}

// Postion and dimensions of the results questions.
//{
constexpr double QUESTION_WIDTH[] = {0.9, 0.03, 0.05};
constexpr double QUESTION_HEIGHT = 0.1;
constexpr double QUESTION_X[] = {0.5, 0.1, 0.2375, 0.375, 0.5, 0.625, 0.7625, 0.9};
constexpr double QUESTION_Y[] = {0.3, 0.433, 0.567, 0.7};
//}

// Positions and dimensions of the mobile number buttons.
//{
constexpr double NUMBER_WIDTH = 0.075;
constexpr double NUMBER_HEIGHT = 0.15;
constexpr double NUMBER_X[] = {
	0.2,
	0.275,
	0.35,
	0.425,
	0.5,
	0.575,
	0.65,
	0.725,
	0.8,
	0.875
};
constexpr double NUMBER_Y = 0.75;
//}

// Position and dimensions of the mobile negative sign button.
//{
constexpr double MINUS_WIDTH = NUMBER_WIDTH;
constexpr double MINUS_HEIGHT = MINUS_WIDTH;
constexpr double MINUS_X = NUMBER_X[0] - MINUS_WIDTH;
constexpr double MINUS_Y = NUMBER_Y;
//}

// Position and dimensions of the next button.
//{
constexpr double NEXT_WIDTH = BEGIN_WIDTH;
constexpr double NEXT_HEIGHT = BEGIN_HEIGHT;
constexpr double NEXT_X = BEGIN_X;
constexpr double NEXT_Y = BEGIN_Y;
//}
//}

// File locations of the sprites.
//{
constexpr const char* BACKGROUND_SOURCE = "data/background.bmp";
constexpr const char* TITLE_SOURCE = "data/title.bmp";
constexpr const char* COPYRIGHT_SOURCE = "data/copyright.bmp";
constexpr const char* START_SOURCE = "data/start.bmp";
constexpr const char* INFO_SOURCE = "data/info.bmp";
constexpr const char* QUIT_SOURCE = "data/quit.bmp";
constexpr const char* INFO_SCREEN_SOURCE = "data/infoscreen.bmp";
constexpr const char* SUM_SOURCE = "data/sum.bmp";
constexpr const char* PRODUCT_SOURCE = "data/product.bmp";
constexpr const char* SET_SOURCE = "data/set.bmp";
constexpr const char* TIME_SOURCE = "data/time.bmp";
constexpr const char* TO_SOURCE = "data/to.bmp";
constexpr const char* BACK_SOURCE = "data/back.bmp";
constexpr const char* BEGIN_SOURCE = "data/begin.bmp";
constexpr const char* UP_SOURCE = "data/up.bmp";
constexpr const char* DOWN_SOURCE = "data/down.bmp";
constexpr const char* MINUS_SOURCE = "data/minus.bmp";
constexpr const char* RESULTS_SOURCE = "data/results.bmp";
constexpr const char* SLASH_SOURCE = "data/slash.bmp";
constexpr const char* PERCENT_SOURCE = "data/percent.bmp";
constexpr const char* LEFT_SOURCE = "data/left.bmp";
constexpr const char* RIGHT_SOURCE = "data/right.bmp";
constexpr const char* NEXT_SOURCE = "data/next.bmp";
//}

// File locations of the number sprites.
constexpr const char* NUMBER_SOURCES[] = {
	"data/0.bmp",
	"data/1.bmp",
	"data/2.bmp",
	"data/3.bmp",
	"data/4.bmp",
	"data/5.bmp",
	"data/6.bmp",
	"data/7.bmp",
	"data/8.bmp",
	"data/9.bmp"
};

// File locations of the operator sprites.
constexpr const char* OPERATOR_SOURCES[] = {
	"data/plus.bmp",
	"data/minus.bmp",
	"data/times.bmp",
	"data/divide.bmp",
	"data/equals.bmp"
};

// File locations of the outcome sprites.
constexpr const char* OUTCOME_SOURCES[] = {
	"data/correct.bmp",
	"data/late.bmp",
	"data/incorrect.bmp"
};

// The file location of the music.
constexpr const char* MUSIC_SOURCE = "data/music.wav";

// The length of the music.
constexpr double MUSIC_LENGTH = 1 * 60 + 47;

// Strings to open the website where developer support is hosted.
constexpr const char* SUPPORT_COMMAND = "explorer ";
constexpr const char* SUPPORT_LINK = "https://gf.me/u/x4rw9t";
//}

// String Conversion
//{
/**
 * Returns a string representation of a signed integer.
 * The first character is either a minus sign or space.
 * The digits parameter represents how many digits from
 *   the value are taken (from smallest to largest).
 */
std::string signed_string(int value, int digits) noexcept {
	std::string string;
	string.resize(digits + 1);
	
	if (value < 0) {
		string[0] = '-';
		value *= -1;
	}
	
	else {
		string[0] = ' ';
	}
	
	for (int i = 0; i < digits; i++) {
		string[digits - i] = '0' + value % 10;
		value /= 10;
	}
	
	return string;
}

/**
 * Returns a string representation of an unsigned integer.
 * The digits parameter represents how many digits from
 *   the value are taken (from smallest to largest).
 */
std::string unsigned_string(int value, int digits) noexcept {
	std::string string;
	string.resize(digits);
	
	for (int i = 0; i < digits; i++) {
		string[digits - 1 - i] = '0' + value % 10;
		value /= 10;
	}
	
	return string;
}
//}

// Quiz Functionality.
//{
int get_digits(int value) noexcept {
	if (value) {
		return log10(abs(value)) + 1;
	}
	
	else {
		return 1;
	}
}

/**
 * Generates and stores a single question.
 * The question can be rendered to the display.
 */
class Question {
	public:
		/**
		 * Generates a single question using the given RNG and distributions.
		 * The question type is determined by op.
		 */
		Question(
			RNG& generator,
			int sum_min,
			int sum_max,
            int product_min,
            int product_max,
			int op
		) noexcept {
			switch (op) {
				case 0:
					operands[0] = generator.get_int(sum_min, sum_max);
					operands[1] = generator.get_int(sum_min, sum_max);
					answer = operands[0] + operands[1];
					break;
					
				case 1:
					answer = generator.get_int(sum_min, sum_max);
					operands[1] = generator.get_int(sum_min, sum_max);
					operands[0] = operands[1] + answer;
					break;
					
				case 2:
					operands[0] = generator.get_int(product_min, product_max);
					operands[1] = generator.get_int(product_min, product_max);
					answer = operands[0] * operands[1];
					break;
					
				case 3:
					answer = generator.get_int(product_min, product_max);
					operands[1] = generator.get_int(product_min, product_max);
					operands[1] = operands[1] ? operands[1] : 1;
					operands[0] = operands[1] * answer;
					break;
			}
			
			operation = op;
		}
		
		/**
		 * Renders the question to the display.
		 * Prompts the user for an answer to the question.
		 * Returns true if the user wishes to stop the test.
		 */
		int question(
			Display& display,
			Button& background,
			Button& back,
			const Renderer& renderer,
			std::array<std::unique_ptr<Sprite>, QUESTION_TYPES + 1>& operators,
			int time_limit
		) {
			// The timer's sprite is set up.
            Button timer(
                Sprite(TIMER_WIDTH * display.width(), TIMER_HEIGHT * display.height()),
                display, TIMER_X, TIMER_Y
            );
			
			// The user's attempt at the answer;
			std::string attempt_string;
			
			// The timer is set up.
			double start = Timer::time();
			
			// A next button for use on mobile devices.
			Button next(Sprite(NEXT_SOURCE, display, NEXT_WIDTH, NEXT_HEIGHT), display, NEXT_X, NEXT_Y);
			
			// A minus button for use on mobile devices.
			Button minus(Sprite(MINUS_SOURCE, display, MINUS_WIDTH, MINUS_HEIGHT), display, MINUS_X, MINUS_Y);
			
			// A vector of number buttons for use on mobile devices.
			std::array<std::unique_ptr<Button>, System::NUMBERS> numbers;
			
			for (int i = 0; i < System::NUMBERS; ++i) {
				numbers[i] = std::make_unique<Button>(
                    Sprite(NUMBER_SOURCES[i], display, NUMBER_WIDTH, NUMBER_HEIGHT),
                    display, NUMBER_X[i], NUMBER_Y
                );
			}
            
			// Handles events.
            Event event;
            
            // True when the questioning ends.
			bool end = false;
            
            // True if the corresponding button was clicked.
            bool next_clicked = false;
            bool back_clicked = false;
            bool minus_clicked = false;
            std::array<bool, System::NUMBERS> numbers_clicked({});
			
			// Loops until the questioning ends.
			while (!end) {
                // The timer's colour is set depending on the remaining time.
				if (time_limit) {
					timer.get_sprite().fill(Sprite::BLACK);
				}
				
				else {
					timer.get_sprite().fill(Sprite::GREEN);
				}
				
				// If time remains, the timer has a portion of its sprite
				//   filled to represent the remaining time.
                double remaining_time = start + time_limit - Timer::time();
                
				if (remaining_time > 0) {
					// The rectangle to be filled in is centred on the timer.
					int width = timer.get_sprite().width();
					int height = timer.get_sprite().height();
					Rectangle time_rectangle(0, 0, width, height);
					
					// The rectangle's height and y-coordinate
					//   depend on the remaining time.
					int new_height =
						time_rectangle.get_height()
						* remaining_time
						/ time_limit
					;
					time_rectangle.set_y(
						time_rectangle.get_y()
						+ time_rectangle.get_height()
						- new_height
					);
					time_rectangle.set_height(new_height);
					
					// The timer is filled in according to the bounds of the rectangle.
					// The colour goes from green at full time to red when almost out of time.
					timer.get_sprite().fill(
						time_rectangle,
						0xff - new_height * 0xff / height,
						new_height * 0xff / height,
						0
					);
				}
				
				// The display is blitted to.
				background.blit_to(display);
				timer.blit_to(display);
				display.blit(*operators[operation], OPERATOR_X, OPERATOR_Y);
				display.blit(*operators[QUESTION_TYPES], EQUALS_X, EQUALS_Y);
				back.blit_to(display);
				next.blit_to(display);
				minus.blit_to(display);
				
				for (int i = 0; i < System::NUMBERS; ++i) {
					numbers[i]->blit_to(display);
				}
				
				// The operands and attempted answer are blitted to the display.
				display.blit(
					renderer.render(
                        display,
						operands[0] < 0
							? signed_string(operands[0], get_digits(operands[0]))
							: unsigned_string(operands[0], get_digits(operands[0]))
						,
						OPERAND_WIDTH,
						OPERAND_HEIGHT
					),
					OPERAND_X[0],
					OPERAND_Y
				);
                
				display.blit(
					renderer.render(
                        display,
						operands[1] < 0
							? signed_string(operands[1], get_digits(operands[1]))
							: unsigned_string(operands[1], get_digits(operands[1]))
						,
						OPERAND_WIDTH,
						OPERAND_HEIGHT
					),
					OPERAND_X[1],
					OPERAND_Y
				);
                
				display.blit(
					renderer.render(
                        display,
						attempt_string,
						ATTEMPT_WIDTH,
						ATTEMPT_HEIGHT
					),
					ATTEMPT_X,
					ATTEMPT_Y
				);
				
				// The display is updated.
				display.update();
                
                // Check for an event.
                while (!end && event.poll()) {
                    // Handle the event.
                    switch (event.type()) {
                        // End the game.
                        case Event::TERMINATE: //{
                            return TERMINATE;
                        //}
                        
                        // Resize (and rotation) handling.
                        case Event::RESIZE: //{
                            // The display is resized.
                            display.resize(event.window_width(), event.window_height());
                            
                            // The sprites are resized.
                            background = Button(Sprite(BACKGROUND_SOURCE, display.width(), display.height()));
                            
                            timer = Button(
                                Sprite(TIMER_WIDTH * display.width(), TIMER_HEIGHT * display.height()),
                                display, TIMER_X, TIMER_Y
                            );
                            
                            back = Button(
                                Sprite(BACK_SOURCE, display, BACK_WIDTH, BACK_HEIGHT),
                                display, BACK_X, BACK_Y
                            );
			
                            next = Button(
                                Sprite(NEXT_SOURCE, display, NEXT_WIDTH, NEXT_HEIGHT),
                                display, NEXT_X, NEXT_Y
                            );
			
                            minus = Button(
                                Sprite(MINUS_SOURCE, display, MINUS_WIDTH, MINUS_HEIGHT),
                                display, MINUS_X, MINUS_Y
                            );
                            
                            for (int i = 0; i <= QUESTION_TYPES; i++) {
                                operators[i] = std::make_unique<Sprite>(
                                    OPERATOR_SOURCES[i], display, OPERATOR_WIDTH, OPERATOR_HEIGHT
                                );
                            }
                            
                            for (int i = 0; i < System::NUMBERS; ++i) {
                                numbers[i] = std::make_unique<Button>(
                                    Sprite(NUMBER_SOURCES[i], display, NUMBER_WIDTH, NUMBER_HEIGHT),
                                    display, NUMBER_X[i], NUMBER_Y
                                );
                            }
                            
                            break;
                        //}
                        
                        // Mouse clicks (and screen touches).
                        case Event::LEFT_CLICK: //{
                            if (next.get_rectangle().contains(event.click_position())) {
                                next_clicked = true;
                            }
                            
                            else if (back.get_rectangle().contains(event.click_position())) {
                                back_clicked = true;
                            }
                            
                            else if (minus.get_rectangle().contains(event.click_position())) {
                                minus_clicked = true;
                            }
                            
                            // Else, the number buttons are checked.
                            else {
                                for (int i = 0; i < System::NUMBERS; ++i) {
                                    if (numbers[i]->get_rectangle().contains(event.click_position())) {
                                        numbers_clicked[i] = true;
                                        break;
                                    }
                                }
                            }
                            
                            break;
                        //}
                        
                        // Mouse (and screen) releases.
                        case Event::LEFT_UNCLICK: //{
                            // If next was clicked, the answer is submitted, if it is valid.
                            if (next_clicked && next.get_rectangle().contains(event.click_position())) {
                                end = submit(attempt_string);
                            }
                            
                            // Else, if back was clicked, the answer's length is checked.
                            else if (back_clicked && back.get_rectangle().contains(event.click_position())) {
                                // Empty answer - quit.
                                if (attempt_string.empty()) {
                                    return QUIT;
                                }
                                
                                // Non-empty answer - backspace.
                                else {
                                    attempt_string.pop_back();
                                }
                            }
                            
                            // Else if minus was clicked, the sign is flipped.
                            else if (minus_clicked && minus.get_rectangle().contains(event.click_position())) {
                                negate(attempt_string);
                            }
                            
                            // Else, the number buttons are checked.
                            else {
                                for (int i = 0; i < System::NUMBERS; ++i) {
                                    if (
                                        numbers_clicked[i]
                                        && numbers[i]->get_rectangle().contains(event.click_position())
                                    ) {
                                        attempt_string += '0' + i;
                                        break;
                                    }
                                }
                            }
                            
                            // The click statuses are reset.
                            next_clicked = false;
                            back_clicked = false;
                            minus_clicked = false;
                            numbers_clicked = {};
                            
                            break;
                        //}
                        
                        // Keyboard input.
                        case Event::KEY_RELEASE: //{
                            // The answer is submitted, if it is valid.
                            if (event.key() == SUBMIT_KEY) {
                                end = submit(attempt_string);
                            }
                            
                            // The last character in the attempt string is removed.
                            else if (event.key() == BACK_KEY) {
                                if (!attempt_string.empty()) {
                                    attempt_string.pop_back();
                                }
                            }
                            
                            // The configuration menu is returned to.
                            else if (event.key() == QUIT_KEY) {
                                return QUIT;
                            }
                            
                            // The sign is flipped.
                            else if (event.key() == MINUS_KEY) {
                                negate(attempt_string);
                            }
                            
                            // The number is entered.
                            else {
                                for (int i = 0; i < System::NUMBERS; ++i) {
                                    if (event.key() == NUMBER_KEYS[i]) {
                                        attempt_string += '0' + i;
                                        break;
                                    }
                                }
                            }
                            
                            break;
                        //}
                    }
                }
			}
			
			// If there was a time limit, but no time remains, the question is marked as late.
			late = time_limit && start + time_limit < Timer::time();
			
            // The attempted answer is stored as an integer.
            attempt = std::stoi(attempt_string);
			
			return 0;
		}
		
		/**
		 * Returns 2 for quick correct answers, 1 for late correct answers, and 0 for incorrect answers.
		 */
		int correct() const noexcept {
			int outcome = 0;
			
			if (answer == attempt) {
				++outcome;
				
				if (!late) {
					++outcome;
				}
			}
			
			return outcome;
		}
		
		/**
		 * Returns a sprite representation of the question.
		 */
		Sprite get_sprite(
			const Sprite& display,
			const Renderer& renderer,
			const std::array<std::unique_ptr<Sprite>, QUESTION_TYPES + 1>& operators,
			const std::array<std::unique_ptr<Sprite>, OUTCOME_TYPES>& outcomes
		) const noexcept {
			// The sprite to be returned.
			Sprite sprite(QUESTION_WIDTH[0] * display.width(), QUESTION_HEIGHT * display.height());
			
			// The first operand is blitted.
			sprite.blit(
				renderer.render(
                    sprite,
					operands[0] < 0
						? signed_string(operands[0], get_digits(operands[0]))
						: unsigned_string(operands[0], get_digits(operands[0]))
					,
					QUESTION_WIDTH[1],
					1
				),
				QUESTION_X[1],
				0.5
			);
			
			// The second operand is blitted.
			sprite.blit(
				renderer.render(
                    sprite,
					operands[1] < 0
						? signed_string(operands[1], get_digits(operands[1]))
						: unsigned_string(operands[1], get_digits(operands[1]))
					,
					QUESTION_WIDTH[1],
					1
				),
				QUESTION_X[3],
				0.5
			);
			
			// The attempt at an answer is blitted.
			sprite.blit(
				renderer.render(
                    sprite,
					attempt < 0
						? signed_string(attempt, get_digits(attempt))
						: unsigned_string(attempt, get_digits(attempt))
					,
					QUESTION_WIDTH[1],
					1
				),
				QUESTION_X[5],
				0.5
			);
			
			// The actual answer is blitted if it was wrong.
			if (attempt != answer) {
				sprite.blit(
					renderer.render(
                        sprite,
						answer < 0
							? signed_string(answer, get_digits(answer))
							: unsigned_string(answer, get_digits(answer))
						,
						QUESTION_WIDTH[1],
						1
					),
					QUESTION_X[7],
					0.5
				);
			}
			
			// The operator is blitted.
			Button(
                Sprite(OPERATOR_SOURCES[operation], sprite, QUESTION_WIDTH[2], 1),
                sprite, QUESTION_X[2], 0.5
			).blit_to(sprite);
			
			// The equals sign is blitted.
			Button(
                Sprite(OPERATOR_SOURCES[4], sprite, QUESTION_WIDTH[2], 1),
                sprite, QUESTION_X[4], 0.5
            ).blit_to(sprite);
			
			// The outcome is blitted.
			int outcome = 2;
			
			if (answer == attempt) {
				outcome--;
				
				if (!late) {
					outcome--;
				}
			}
			
			sprite.blit(*outcomes[outcome], QUESTION_X[6], 0.5);
			
			return sprite;
		}
        
	private:
        /**
         * Flips the answer's sign.
         */
        static void negate(std::string& attempt_string) noexcept {
            if (attempt_string.empty()) {
                attempt_string.push_back('-');
            }
            
            else if (attempt_string[0] != '-') {
                attempt_string.insert(0, 1, '-');
            }
            
            else {
                attempt_string.erase(0, 1);
            }
        }
        
        /**
         * Returns true for a valid answer.
         */
        static bool submit(const std::string& attempt_string) noexcept {
            return !attempt_string.empty() && '0' <= attempt_string.back() && attempt_string.back() <= '9';
        }
        
		std::array<int, 2> operands; // The two operands in the operation.
		int answer;                  // The answer to the operation.
		int operation;               // The operation code (+-*/).
		int attempt;                 // The user's attempt at an answer.
		bool late;                   // True if the user answered too late.
};

/**
 * Displays the results of the test.
 * The overall score is shown as a fraction and percentage.
 * Each question can be viewed along with the given and true answer.
 */
bool results(
	Display& display,
	Button& background,
	Button& back,
	const Renderer& renderer,
	const std::vector<Question>& questions,
	std::array<std::unique_ptr<Sprite>, QUESTION_TYPES + 1>& operators,
	int set_count
) noexcept {
	// The user's total score in the test is calculated.
	int score = 0;
	
	for (int i = 0; i < QUESTION_TYPES * set_count; i++) {
		score += questions[i].correct();
	}
	
	// The current results page.
	int page = 0;
    
    // The sprites are loaded.
    Button res(Sprite(RESULTS_SOURCE, display, RESULTS_WIDTH, RESULTS_HEIGHT), display, RESULTS_X, RESULTS_Y);
    Button slash(Sprite(SLASH_SOURCE, display, SLASH_WIDTH, SLASH_HEIGHT), display, SLASH_X, SLASH_Y);
    Button percent(Sprite(PERCENT_SOURCE, display, PERCENT_WIDTH, PERCENT_HEIGHT), display, PERCENT_X, PERCENT_Y);
	Button left(Sprite(LEFT_SOURCE, display, LEFT_WIDTH, LEFT_HEIGHT), display, LEFT_X, LEFT_Y);
	Button right(Sprite(RIGHT_SOURCE, display, RIGHT_WIDTH, RIGHT_HEIGHT), display, RIGHT_X, RIGHT_Y);
	
	// The sprites for the outcomes are loaded.
	std::array<std::unique_ptr<Sprite>, OUTCOME_TYPES> outcomes;
	
	for (int i = 0; i < OUTCOME_TYPES; i++) {
		outcomes[i] = std::make_unique<Sprite>(
			OUTCOME_SOURCES[i],
            display,
			QUESTION_WIDTH[2] * QUESTION_WIDTH[0],
			QUESTION_HEIGHT
		);
	}
    
    // Handles events.
    Event event;
	
	// True when the results should no longer be displayed.
	bool end = false;
    
    // True if the corresponding button was clicked.
    bool left_clicked = false;
    bool right_clicked = false;
    bool back_clicked = false;
	
	// The display is filled with the test's information with each loop.
	while (!end) {
		// The display is blitted to.
		background.blit_to(display);
		res.blit_to(display);
		slash.blit_to(display);
		percent.blit_to(display);
		back.blit_to(display);
		
		// The arrows are only displayed if they can be used.
		if (page) {
			left.blit_to(display);
		}
		
		if (page < set_count - 1) {
			right.blit_to(display);
		}
		
		// The score is blitted to the display.
		display.blit(
			renderer.render(
                display,
				unsigned_string(score, get_digits(score)),
				SCORE_WIDTH,
				SCORE_HEIGHT
			),
			SCORE_X,
			SCORE_Y
		);
		
		// The total number of questions are blitted to the display.
		display.blit(
			renderer.render(
                display,
				unsigned_string(
					2 * QUESTION_TYPES * set_count,
					get_digits(2 * QUESTION_TYPES * set_count)
				),
				TOTAL_WIDTH,
				TOTAL_HEIGHT
			),
			TOTAL_X,
			TOTAL_Y
		);
		
		// The percentage of questions answered correctly.
		display.blit(
			renderer.render(
                display,
				unsigned_string(
					50 * score / (QUESTION_TYPES * set_count),
					get_digits(50 * score / (QUESTION_TYPES * set_count))
				),
				PERCENTAGE_WIDTH,
				PERCENTAGE_HEIGHT
			),
			PERCENTAGE_X,
			PERCENTAGE_Y
		);
		
		// The question set in the page is displayed.
		for (int i = 0; i < QUESTION_TYPES; i++) {
			display.blit(
				questions[QUESTION_TYPES * page + i].get_sprite(
					display,
					renderer,
					operators,
					outcomes
				),
				QUESTION_X[0],
				QUESTION_Y[i]
			);
		}
		
		// The display is updated.
		display.update();
        
        // Check for an event.
        while (!end && event.poll()) {
            //Handle the event.
            switch (event.type()) {
                // End the game.
                case Event::TERMINATE: //{
                    return true;
                //}
                
                // Resize (and rotation) handling.
                case Event::RESIZE: //{
                    // The display is resized.
                    display.resize(event.window_width(), event.window_height());
                    
                    // The sprites are resized.
                    background = Button(Sprite(BACKGROUND_SOURCE, display.width(), display.height()));
                    
                    res = Button(
                        Sprite(RESULTS_SOURCE, display, RESULTS_WIDTH, RESULTS_HEIGHT),
                        display, RESULTS_X, RESULTS_Y
                    );
                    
                    slash = Button(
                        Sprite(SLASH_SOURCE, display, SLASH_WIDTH, SLASH_HEIGHT),
                        display, SLASH_X, SLASH_Y
                    );
                    
                    percent = Button(
                        Sprite(PERCENT_SOURCE, display, PERCENT_WIDTH, PERCENT_HEIGHT),
                        display, PERCENT_X, PERCENT_Y
                    );
                    
                    back = Button(
                        Sprite(BACK_SOURCE, display, BACK_WIDTH, BACK_HEIGHT),
                        display, BACK_X, BACK_Y
                    );
                    
                    left = Button(Sprite(LEFT_SOURCE, display, LEFT_WIDTH, LEFT_HEIGHT), display, LEFT_X, LEFT_Y);
                    right = Button(Sprite(RIGHT_SOURCE, display, RIGHT_WIDTH, RIGHT_HEIGHT), display, RIGHT_X, RIGHT_Y);
                    
                    break;
                //}
            
                // Mouse clicks (and screen touches).
                case Event::LEFT_CLICK: //{
                    if (left.get_rectangle().contains(event.click_position())) {
                        left_clicked = true;
                    }
                    
                    else if (right.get_rectangle().contains(event.click_position())) {
                        right_clicked = true;
                    }
                    
                    else if (back.get_rectangle().contains(event.click_position())) {
                        back_clicked = true;
                    }
                    
                    break;
                //}
                
                // Mouse (and screen) releases.
                case Event::LEFT_UNCLICK: //{
                    // Previous page.
                    if (left_clicked && left.get_rectangle().contains(event.click_position())) {
                        if (page) {
                            --page;
                        }
                    }
                    
                    // Next page.
                    else if (right_clicked && right.get_rectangle().contains(event.click_position())) {
                        if (page < set_count - 1) {
                            ++page;
                        }
                    }
                    
                    // The configuration menu is returned to.
                    else if (back_clicked && back.get_rectangle().contains(event.click_position())) {
                        end = true;
                    }
                    
                    // The click statuses are reset.
                    left_clicked = false;
                    right_clicked = false;
                    back_clicked = false;
                    
                    break;
                //}
                
                // Keyboard input.
                case Event::KEY_RELEASE: //{
                    // Previous page.
                    if (event.key() == PREVIOUS_KEY) {
                        if (page) {
                            --page;
                        }
                    }
                    
                    // Next page.
                    else if (event.key() == NEXT_KEY) {
                        if (page < set_count - 1) {
                            ++page;
                        }
                    }
                    
                    // The configuration menu is returned to.
                    else if (event.key() == QUIT_KEY) {
                        end = true;
                    }
                    
                    break;
                //}
            }
        }
		
        #ifdef AUTOSCHOOLMATHS_V1
		// Loop for user input.
		while (true) {
			Point mouse;
			
			// If the quit key was pressed, the function returns.
			if (Events::unpress(QUIT_KEY)) {
				end = true;
				break;
			}
			
			// Else, if the left arrow was pressed, the previous page is moved to.
			else if (page && Events::unpress(PREVIOUS_KEY)) {
				page--;
				break;
			}
			
			// Else, if the right arrow was pressed, the next page is moved to.
			else if (
				page < set_count - 1
				&& Events::unpress(NEXT_KEY)
			) {
				page++;
				break;
			}
			
			// Else, if the mouse was clicked and released, its position is stored.
			else if (Events::unclick(Events::LEFT_CLICK, mouse)) {
				// If the back button was clicked, the function returns.
				if (back_button.get_rectangle().contains(mouse)) {
					end = true;
					break;
				}
				
				// Else, if the left button was pressed, the previous page
				//   is moved to (if possible).
				else if (page && left_button.get_rectangle().contains(mouse)) {
					page--;
					break;
				}
				
				// Else, if the right button was pressed, the next page
				//   is moved to (is possible).
				else if (
					page < set_count - 1
					&& right_button.get_rectangle().contains(mouse)
				) {
					page++;
					break;
				}
			}
			
			Events::update();
		}
        #endif
	}
    
    return false;
}

/**
 * Runs the test using the given settings.
 */
bool test(
	Display& display,
	Button& background,
	Button& back,
	const Renderer& renderer,
	const std::array<int, 2>& sum_range,
	const std::array<int, 2>& product_range,
	int set_count,
	int time_limit
) noexcept {
	// The RNG and distributions are initialised.
	RNG generator;
	int sum_min = sum_range[0] < sum_range[1] ? sum_range[0] : sum_range[1];
	int sum_max = sum_range[0] > sum_range[1] ? sum_range[0] : sum_range[1];
	int product_min = product_range[0] < product_range[1] ? product_range[0] : product_range[1];
	int product_max = product_range[0] > product_range[1] ? product_range[0] : product_range[1];
	
	// The sprites for the operators are loaded.
	std::array<std::unique_ptr<Sprite>, QUESTION_TYPES + 1> operators;
	
	for (int i = 0; i <= QUESTION_TYPES; i++) {
		operators[i] = std::make_unique<Sprite>(OPERATOR_SOURCES[i], display, OPERATOR_WIDTH, OPERATOR_HEIGHT);
	}
	
	// True if the questions were completed.
	bool finished = true;
	
	// The vector of questions is initialised and the questions are asked.
	std::vector<Question> questions;
	
	for (int i = 0; i < QUESTION_TYPES * set_count; i++) {
		questions.push_back(
            Question(
                generator,
                sum_min,
                sum_max,
                product_min,
                product_max,
                i % QUESTION_TYPES
            )
        );
        
        int code = questions[i].question(
			display,
			background,
			back,
			renderer,
			operators,
			time_limit
		);
        
        if (code == TERMINATE) {
            return true;
        }
		
		else if (code == QUIT) {
			finished = false;
			break;
		}
	}
	
    if (finished) {
		return results(
			display,
			background,
			back,
			renderer,
			questions,
			operators,
			set_count
		);
	}
    
    return false;
}
//}

// Configuration Menu
//{
// Arrow rectangle initialisation.
//{
/**
 * Sets the rectangles for the sum arrows.
 */
void set_sum_rectangles(
    const Sprite& display,
    std::array<Rectangle, SUM_DIGITS + 1>& sum_min_up_rectangles,
    std::array<Rectangle, SUM_DIGITS + 1>& sum_min_down_rectangles,
    std::array<Rectangle, SUM_DIGITS + 1>& sum_max_up_rectangles,
    std::array<Rectangle, SUM_DIGITS + 1>& sum_max_down_rectangles
) noexcept {
    for (int i = 0; i <= SUM_DIGITS; i++) {
		sum_min_up_rectangles[i].set_width(UP_WIDTH * display.width());
		sum_min_up_rectangles[i].set_height(UP_HEIGHT * display.height());
		sum_min_up_rectangles[i].set(display.width(), display.height(), SUM_MIN_X, SUM_MIN_Y);
		sum_min_up_rectangles[i].set_x(
			sum_min_up_rectangles[i].get_x()
			- SUM_DIGITS * sum_min_up_rectangles[i].get_width() / 2
			+ i * sum_min_up_rectangles[i].get_width()
		);
		sum_min_up_rectangles[i].set_y(
			sum_min_up_rectangles[i].get_y()
			- (
				SUM_MIN_HEIGHT * display.height()
				+ sum_min_up_rectangles[i].get_height()
			) / 2
		);
		
		sum_min_down_rectangles[i].set_width(DOWN_WIDTH * display.width());
		sum_min_down_rectangles[i].set_height(DOWN_HEIGHT * display.height());
		sum_min_down_rectangles[i].set(display.width(), display.height(), SUM_MIN_X, SUM_MIN_Y);
		sum_min_down_rectangles[i].set_x(sum_min_up_rectangles[i].get_x());
		sum_min_down_rectangles[i].set_y(
			sum_min_down_rectangles[i].get_y()
			+ (
				SUM_MIN_HEIGHT * display.height()
				+ sum_min_down_rectangles[i].get_height()
			) / 2
		);
		
		sum_max_up_rectangles[i].set_width(UP_WIDTH * display.width());
		sum_max_up_rectangles[i].set_height(UP_HEIGHT * display.height());
		sum_max_up_rectangles[i].set(display.width(), display.height(), SUM_MAX_X, SUM_MAX_Y);
		sum_max_up_rectangles[i].set_x(
			sum_max_up_rectangles[i].get_x()
			- SUM_DIGITS * sum_max_up_rectangles[i].get_width() / 2
			+ i * sum_max_up_rectangles[i].get_width()
		);
		sum_max_up_rectangles[i].set_y(sum_min_up_rectangles[i].get_y());
		
		sum_max_down_rectangles[i].set_width(DOWN_WIDTH * display.width());
		sum_max_down_rectangles[i].set_height(DOWN_HEIGHT * display.height());
		sum_max_down_rectangles[i].set_x(sum_max_up_rectangles[i].get_x());
		sum_max_down_rectangles[i].set_y(sum_min_down_rectangles[i].get_y());
	}
}

/**
 *
 */
void set_product_rectangles(
    const Sprite& display,
    std::array<Rectangle, PRODUCT_DIGITS + 1>& product_min_up_rectangles,
    std::array<Rectangle, PRODUCT_DIGITS + 1>& product_min_down_rectangles,
    std::array<Rectangle, PRODUCT_DIGITS + 1>& product_max_up_rectangles,
    std::array<Rectangle, PRODUCT_DIGITS + 1>& product_max_down_rectangles
) noexcept {
    for (int i = 0; i <= PRODUCT_DIGITS; i++) {
		product_min_up_rectangles[i].set_width(UP_WIDTH * display.width());
		product_min_up_rectangles[i].set_height(UP_HEIGHT * display.height());
		product_min_up_rectangles[i].set(display.width(), display.height(), PRODUCT_MIN_X, PRODUCT_MIN_Y);
		product_min_up_rectangles[i].set_x(
			product_min_up_rectangles[i].get_x()
			- PRODUCT_DIGITS * product_min_up_rectangles[i].get_width() / 2
			+ i * product_min_up_rectangles[i].get_width()
		);
		product_min_up_rectangles[i].set_y(
			product_min_up_rectangles[i].get_y()
			- (
				PRODUCT_MIN_HEIGHT * display.height()
				+ product_min_up_rectangles[i].get_height()
			) / 2
		);
		
		product_min_down_rectangles[i].set_width(DOWN_WIDTH * display.width());
		product_min_down_rectangles[i].set_height(DOWN_HEIGHT * display.height());
		product_min_down_rectangles[i].set(display.width(), display.height(), PRODUCT_MIN_X, PRODUCT_MIN_Y);
		product_min_down_rectangles[i].set_x(product_min_up_rectangles[i].get_x());
		product_min_down_rectangles[i].set_y(
			product_min_down_rectangles[i].get_y()
			+ (
				PRODUCT_MIN_HEIGHT * display.height()
				+ product_min_down_rectangles[i].get_height()
			) / 2
		);
		
		product_max_up_rectangles[i].set_width(UP_WIDTH * display.width());
		product_max_up_rectangles[i].set_height(UP_HEIGHT * display.height());
		product_max_up_rectangles[i].set(display.width(), display.height(), PRODUCT_MAX_X, PRODUCT_MAX_Y);
		product_max_up_rectangles[i].set_x(
			product_max_up_rectangles[i].get_x()
			- PRODUCT_DIGITS * product_max_up_rectangles[i].get_width() / 2
			+ i * product_max_up_rectangles[i].get_width()
		);
		product_max_up_rectangles[i].set_y(product_min_up_rectangles[i].get_y());
		
		product_max_down_rectangles[i].set_width(DOWN_WIDTH * display.width());
		product_max_down_rectangles[i].set_height(DOWN_HEIGHT * display.height());
		product_max_down_rectangles[i].set_x(product_max_up_rectangles[i].get_x());
		product_max_down_rectangles[i].set_y(product_min_down_rectangles[i].get_y());
	}
}

/**
 *
 */
void set_set_rectangles(
    const Sprite& display,
    std::array<Rectangle, SET_DIGITS>& set_count_up_rectangles,
    std::array<Rectangle, SET_DIGITS>& set_count_down_rectangles
) noexcept {
    for (int i = 0; i < SET_DIGITS; i++) {
		set_count_up_rectangles[i].set_width(UP_WIDTH * display.width());
		set_count_up_rectangles[i].set_height(UP_HEIGHT * display.height());
		set_count_up_rectangles[i].set(display.width(), display.height(), SET_COUNT_X, SET_COUNT_Y);
		set_count_up_rectangles[i].set_x(
			set_count_up_rectangles[i].get_x()
			- (SET_DIGITS - 1) * set_count_up_rectangles[i].get_width() / 2
			+ i * set_count_up_rectangles[i].get_width()
		);
		set_count_up_rectangles[i].set_y(
			set_count_up_rectangles[i].get_y()
			- (
				SET_COUNT_HEIGHT * display.height()
				+ set_count_up_rectangles[i].get_height()
			) / 2
		);
		
		set_count_down_rectangles[i].set_width(DOWN_WIDTH * display.width());
		set_count_down_rectangles[i].set_height(DOWN_HEIGHT * display.height());
		set_count_down_rectangles[i].set(display.width(), display.height(), SET_COUNT_X, SET_COUNT_Y);
		set_count_down_rectangles[i].set_x(set_count_up_rectangles[i].get_x());
		set_count_down_rectangles[i].set_y(
			set_count_down_rectangles[i].get_y()
			+ (
				SET_COUNT_HEIGHT * display.height()
				+ set_count_down_rectangles[i].get_height()
			) / 2
		);
	}
}

/**
 *
 */
void set_time_rectangles(
    const Sprite& display,
    std::array<Rectangle, TIME_DIGITS>& time_limit_up_rectangles,
    std::array<Rectangle, TIME_DIGITS>& time_limit_down_rectangles
) noexcept {
    for (int i = 0; i < TIME_DIGITS; i++) {
		time_limit_up_rectangles[i].set_width(UP_WIDTH * display.width());
		time_limit_up_rectangles[i].set_height(UP_HEIGHT * display.height());
		time_limit_up_rectangles[i].set(display.width(), display.height(), TIME_LIMIT_X, TIME_LIMIT_Y);
		time_limit_up_rectangles[i].set_x(
			time_limit_up_rectangles[i].get_x()
			- (TIME_DIGITS - 1) * time_limit_up_rectangles[i].get_width() / 2
			+ i * time_limit_up_rectangles[i].get_width()
		);
		time_limit_up_rectangles[i].set_y(
			time_limit_up_rectangles[i].get_y()
			- (
				TIME_LIMIT_HEIGHT * display.height()
				+ time_limit_up_rectangles[i].get_height()
			) / 2
		);
		
		time_limit_down_rectangles[i].set_width(DOWN_WIDTH * display.width());
		time_limit_down_rectangles[i].set_height(DOWN_HEIGHT * display.height());
		time_limit_down_rectangles[i].set(display.width(), display.height(), TIME_LIMIT_X, TIME_LIMIT_Y);
		time_limit_down_rectangles[i].set_x(time_limit_up_rectangles[i].get_x());
		time_limit_down_rectangles[i].set_y(
			time_limit_down_rectangles[i].get_y()
			+ (
				TIME_LIMIT_HEIGHT * display.height()
				+ time_limit_down_rectangles[i].get_height()
			) / 2
		);
	}
}
//}

/**
 * Returns values to their bounds if they go beyond them.
 */
void fix_values(
	std::array<int, 2>& sum_range,
	std::array<int, 2>& product_range,
	int& set_count,
	int& time_limit
) noexcept {
	if (sum_range[0] < SUM_RANGE[0]) {
		sum_range[0] = SUM_RANGE[0];
	}
	
	else if (sum_range[0] > SUM_RANGE[1]) {
		sum_range[0] = SUM_RANGE[1];
	}
	
	if (sum_range[1] < SUM_RANGE[0]) {
		sum_range[1] = SUM_RANGE[0];
	}
	
	else if (sum_range[1] > SUM_RANGE[1]) {
		sum_range[1] = SUM_RANGE[1];
	}
	
	if (product_range[0] < PRODUCT_RANGE[0]) {
		product_range[0] = PRODUCT_RANGE[0];
	}
	
	else if (product_range[0] > PRODUCT_RANGE[1]) {
		product_range[0] = PRODUCT_RANGE[1];
	}
	
	if (product_range[1] < PRODUCT_RANGE[0]) {
		product_range[1] = PRODUCT_RANGE[0];
	}
	
	else if (product_range[1] > PRODUCT_RANGE[1]) {
		product_range[1] = PRODUCT_RANGE[1];
	}
	
	if (set_count < SET_RANGE[0]) {
		set_count = SET_RANGE[0];
	}
	
	else if (set_count > SET_RANGE[1]) {
		set_count = SET_RANGE[1];
	}
	
	if (time_limit < TIME_RANGE[0]) {
		time_limit = TIME_RANGE[0];
	}
	
	else if (time_limit > TIME_RANGE[1]) {
		time_limit = TIME_RANGE[1];
	}
}

/**
 * Resizes the configuration menu's sprites.
 */
void resize_configure(
    const Display& display,
    Button& background,
    Button& sum,
    Button& product,
    Button& set,
    Button& time,
    Sprite& to,
    Button& back,
    Button& begin,
    Sprite& up_arrow,
    Sprite& down_arrow,
    std::array<Rectangle, SUM_DIGITS + 1>& sum_min_up_rectangles,
    std::array<Rectangle, SUM_DIGITS + 1>& sum_min_down_rectangles,
    std::array<Rectangle, SUM_DIGITS + 1>& sum_max_up_rectangles,
    std::array<Rectangle, SUM_DIGITS + 1>& sum_max_down_rectangles,
    std::array<Rectangle, PRODUCT_DIGITS + 1>& product_min_up_rectangles,
    std::array<Rectangle, PRODUCT_DIGITS + 1>& product_min_down_rectangles,
    std::array<Rectangle, PRODUCT_DIGITS + 1>& product_max_up_rectangles,
    std::array<Rectangle, PRODUCT_DIGITS + 1>& product_max_down_rectangles,
    std::array<Rectangle, SET_DIGITS>& set_count_up_rectangles,
    std::array<Rectangle, SET_DIGITS>& set_count_down_rectangles,
    std::array<Rectangle, TIME_DIGITS>& time_limit_up_rectangles,
    std::array<Rectangle, TIME_DIGITS>& time_limit_down_rectangles
) noexcept {
    background = Button(Sprite(BACKGROUND_SOURCE, display.width(), display.height()));
    sum = Button(Sprite(SUM_SOURCE, display, SUM_WIDTH, SUM_HEIGHT), display, SUM_X, SUM_Y);
    product = Button(
        Sprite(PRODUCT_SOURCE, display, PRODUCT_WIDTH, PRODUCT_HEIGHT),
        display, PRODUCT_X, PRODUCT_Y
    );
    set = Button(Sprite(SET_SOURCE, display, SET_WIDTH, SET_HEIGHT), display, SET_X, SET_Y);
    time = Button(Sprite(TIME_SOURCE, display, TIME_WIDTH, TIME_HEIGHT), display, TIME_X, TIME_Y);
    to = Sprite(TO_SOURCE, display, TO_WIDTH, TO_HEIGHT);
    back = Button(Sprite(BACK_SOURCE, display, BACK_WIDTH, BACK_HEIGHT), display, BACK_X, BACK_Y);
    begin = Button(Sprite(BEGIN_SOURCE, display, BEGIN_WIDTH, BEGIN_HEIGHT), display, BEGIN_X, BEGIN_Y);
    up_arrow = Sprite(UP_SOURCE, display, UP_WIDTH, UP_HEIGHT);
    down_arrow = Sprite(DOWN_SOURCE, display, DOWN_WIDTH, DOWN_HEIGHT);
    
    // The rectangles are resized.
    set_sum_rectangles(
        display,
        sum_min_up_rectangles,
        sum_min_down_rectangles,
        sum_max_up_rectangles,
        sum_max_down_rectangles
    );
    
    set_product_rectangles(
        display,
        product_min_up_rectangles,
        product_min_down_rectangles,
        product_max_up_rectangles,
        product_max_down_rectangles
    );
    
    set_set_rectangles(
        display,
        set_count_up_rectangles,
        set_count_down_rectangles
    );
    
    set_time_rectangles(
        display,
        time_limit_up_rectangles,
        time_limit_down_rectangles
    );
}

/**
 * Configures the Maths test's number range, question count, and time per question.
 */
bool configure(Display& display, Button& background) noexcept {
	// The test is configured to the default settings.
	std::array<int, 2> sum_range = {SUM_MIN, SUM_MAX};
	std::array<int, 2> product_range = {PRODUCT_MIN, PRODUCT_MAX};
	int set_count = SET_COUNT;
	int time_limit = TIME_LIMIT;
	
	// The configuration menu sprites are intialised.
    Button sum(Sprite(SUM_SOURCE, display, SUM_WIDTH, SUM_HEIGHT), display, SUM_X, SUM_Y);
    Button product(Sprite(PRODUCT_SOURCE, display, PRODUCT_WIDTH, PRODUCT_HEIGHT), display, PRODUCT_X, PRODUCT_Y);
    Button set(Sprite(SET_SOURCE, display, SET_WIDTH, SET_HEIGHT), display, SET_X, SET_Y);
    Button time(Sprite(TIME_SOURCE, display, TIME_WIDTH, TIME_HEIGHT), display, TIME_X, TIME_Y);
    Sprite to(TO_SOURCE, display, TO_WIDTH, TO_HEIGHT);
	Button back(Sprite(BACK_SOURCE, display, BACK_WIDTH, BACK_HEIGHT), display, BACK_X, BACK_Y);
	Button begin(Sprite(BEGIN_SOURCE, display, BEGIN_WIDTH, BEGIN_HEIGHT), display, BEGIN_X, BEGIN_Y);
	Sprite up_arrow(UP_SOURCE, display, UP_WIDTH, UP_HEIGHT);
	Sprite down_arrow(DOWN_SOURCE, display, DOWN_WIDTH, DOWN_HEIGHT);
    
    // A signed integer renderer is initialised.
    std::array<char, System::NUMBERS + 1> chars;
    std::array<std::string, System::NUMBERS + 1> sources;
    chars[System::NUMBERS] = '-';
    sources[System::NUMBERS] = MINUS_SOURCE;
    
    for (int i = 0; i < System::NUMBERS; ++i) {
        chars[i] = '0' + i;
        sources[i] = NUMBER_SOURCES[i];
    }
    
	const Renderer& renderer = FullRenderer<System::NUMBERS + 1>(chars, sources);
	
	// The rectangles for the up and down arrows are initialised.
	//   Sum rectangles
	std::array<Rectangle, SUM_DIGITS + 1> sum_min_up_rectangles;
	std::array<Rectangle, SUM_DIGITS + 1> sum_min_down_rectangles;
	std::array<Rectangle, SUM_DIGITS + 1> sum_max_up_rectangles;
	std::array<Rectangle, SUM_DIGITS + 1> sum_max_down_rectangles;
    set_sum_rectangles(
        display,
        sum_min_up_rectangles,
        sum_min_down_rectangles,
        sum_max_up_rectangles,
        sum_max_down_rectangles
    );
    
	//   Product rectangles
	std::array<Rectangle, PRODUCT_DIGITS + 1> product_min_up_rectangles;
	std::array<Rectangle, PRODUCT_DIGITS + 1> product_min_down_rectangles;
	std::array<Rectangle, PRODUCT_DIGITS + 1> product_max_up_rectangles;
	std::array<Rectangle, PRODUCT_DIGITS + 1> product_max_down_rectangles;
    set_product_rectangles(
        display,
        product_min_up_rectangles,
        product_min_down_rectangles,
        product_max_up_rectangles,
        product_max_down_rectangles
    );
    
	//   Question set count rectangles
	std::array<Rectangle, SET_DIGITS> set_count_up_rectangles;
	std::array<Rectangle, SET_DIGITS> set_count_down_rectangles;
    set_set_rectangles(
        display,
        set_count_up_rectangles,
        set_count_down_rectangles
    );
    
	//   Time limit rectangles
	std::array<Rectangle, TIME_DIGITS> time_limit_up_rectangles;
	std::array<Rectangle, TIME_DIGITS> time_limit_down_rectangles;
    set_time_rectangles(
        display,
        time_limit_up_rectangles,
        time_limit_down_rectangles
    );
    
    // Handles events.
    Event event;
    
	// True when the configuration loop should end.
    bool end = false;
    
    // True if the corresponding button was clicked.
    bool begin_clicked = false;
    bool back_clicked = false;
    bool sum_min_sign_clicked = false;
    bool sum_max_sign_clicked = false;
    bool product_min_sign_clicked = false;
    bool product_max_sign_clicked = false;
    
	// Loop for the configuration menu.
	// The configuration menu is displayed with each loop.
	while (!end) {
		// Values that were moved out of range are moved back in range.
		fix_values(sum_range, product_range, set_count, time_limit);
		
		// The display is blitted to and updated.
		//   Basic sprites are blitted.
		background.blit_to(display);
		sum.blit_to(display);
		product.blit_to(display);
		set.blit_to(display);
		time.blit_to(display);
		display.blit(to, TO_X[0], TO_Y[0]);
		display.blit(to, TO_X[1], TO_Y[1]);
		back.blit_to(display);
		begin.blit_to(display);
		
		//   Rendered numbers are blitted.
		display.blit(
			renderer.render(
                display,
				signed_string(sum_range[0], SUM_DIGITS),
				SUM_MIN_WIDTH,
				SUM_MIN_HEIGHT
			),
			SUM_MIN_X,
			SUM_MIN_Y
		);
        
		display.blit(
			renderer.render(
                display,
				signed_string(sum_range[1], SUM_DIGITS),
				SUM_MAX_WIDTH,
				SUM_MAX_HEIGHT
			),
			SUM_MAX_X,
			SUM_MAX_Y
		);
        
		display.blit(
			renderer.render(
                display,
				signed_string(product_range[0], PRODUCT_DIGITS),
				PRODUCT_MIN_WIDTH,
				PRODUCT_MIN_HEIGHT
			),
			PRODUCT_MIN_X,
			PRODUCT_MIN_Y
		);
        
		display.blit(
			renderer.render(
                display,
				signed_string(product_range[1], PRODUCT_DIGITS),
				PRODUCT_MAX_WIDTH,
				PRODUCT_MAX_HEIGHT
			),
			PRODUCT_MAX_X,
			PRODUCT_MAX_Y
		);
        
		display.blit(
			renderer.render(
                display,
				unsigned_string(set_count, SET_DIGITS),
				SET_COUNT_WIDTH,
				SET_COUNT_HEIGHT
			),
			SET_COUNT_X,
			SET_COUNT_Y
		);
        
		display.blit(
			renderer.render(
                display,
				unsigned_string(time_limit, TIME_DIGITS),
				TIME_LIMIT_WIDTH,
				TIME_LIMIT_HEIGHT
			),
			TIME_LIMIT_X,
			TIME_LIMIT_Y
		);
		
		//   Arrow pseudo-buttons are blitted.
		for (int i = 0; i <= SUM_DIGITS; i++) {
			display.blit(up_arrow, sum_min_up_rectangles[i]);
			display.blit(down_arrow, sum_min_down_rectangles[i]);
			display.blit(up_arrow, sum_max_up_rectangles[i]);
			display.blit(down_arrow, sum_max_down_rectangles[i]);
		}
		
		for (int i = 0; i <= PRODUCT_DIGITS; i++) {
			display.blit(up_arrow, product_min_up_rectangles[i]);
			display.blit(down_arrow, product_min_down_rectangles[i]);
			display.blit(up_arrow, product_max_up_rectangles[i]);
			display.blit(down_arrow, product_max_down_rectangles[i]);
		}
		
		for (int i = 0; i < SET_DIGITS; i++) {
			display.blit(up_arrow, set_count_up_rectangles[i]);
			display.blit(down_arrow, set_count_down_rectangles[i]);
		}
		
		for (int i = 0; i < TIME_DIGITS; i++) {
			display.blit(up_arrow, time_limit_up_rectangles[i]);
			display.blit(down_arrow, time_limit_down_rectangles[i]);
		}
		
		//   The display is updated.
		display.update();
        
        // Check for an event.
        while (!end && event.poll()) {
            // Handle the event.
            switch (event.type()) {
                // End the game.
                case Event::TERMINATE: //{
                    return true;
                //}
                
                // Resize (and rotation) handling.
                case Event::RESIZE: //{
                    // The display is resized.
                    display.resize(event.window_width(), event.window_height());
                    
                    // The sprites are resized.
                    resize_configure(
                        display,
                        background,
                        sum,
                        product,
                        set,
                        time,
                        to,
                        back,
                        begin,
                        up_arrow,
                        down_arrow,
                        sum_min_up_rectangles,
                        sum_min_down_rectangles,
                        sum_max_up_rectangles,
                        sum_max_down_rectangles,
                        product_min_up_rectangles,
                        product_min_down_rectangles,
                        product_max_up_rectangles,
                        product_max_down_rectangles,
                        set_count_up_rectangles,
                        set_count_down_rectangles,
                        time_limit_up_rectangles,
                        time_limit_down_rectangles
                    );

                    break;
                //}
                
                // Mouse clicks (and screen touches).
                case Event::LEFT_CLICK: //{
                    if (begin.get_rectangle().contains(event.click_position())) {
                        begin_clicked = true;
                    }
                    
                    else if (
                        sum_min_up_rectangles[0].contains(event.click_position())
                        || sum_min_down_rectangles[0].contains(event.click_position())
                    ) {
                        sum_min_sign_clicked = true;
                    }
                    
                    else if (
                        sum_max_up_rectangles[0].contains(event.click_position())
                        || sum_max_down_rectangles[0].contains(event.click_position())
                    ) {
                        sum_max_sign_clicked = true;
                    }
                    
                    else if (
                        product_min_up_rectangles[0].contains(event.click_position())
                        || product_min_down_rectangles[0].contains(event.click_position())
                    ) {
                        product_min_sign_clicked = true;
                    }
                    
                    else if (
                        product_max_up_rectangles[0].contains(event.click_position())
                        || product_max_down_rectangles[0].contains(event.click_position())
                    ) {
                        product_max_sign_clicked = true;
                    }
                    
                    else if (back.get_rectangle().contains(event.click_position())) {
                        back_clicked = true;
                    }
                    
                    break;
                //}
                
                // Mouse (and screen) releases.
                case Event::LEFT_UNCLICK: //{
                    // If begin was clicked, the quiz begins.
                    if (begin_clicked && begin.get_rectangle().contains(event.click_position())) {
                        if (test(
                            display,
                            background,
                            back,
                            renderer,
                            sum_range,
                            product_range,
                            set_count,
                            time_limit
                        )) {
                            return true;
                        }
                        
                        // The sprites are resized.
                        resize_configure(
                            display,
                            background,
                            sum,
                            product,
                            set,
                            time,
                            to,
                            back,
                            begin,
                            up_arrow,
                            down_arrow,
                            sum_min_up_rectangles,
                            sum_min_down_rectangles,
                            sum_max_up_rectangles,
                            sum_max_down_rectangles,
                            product_min_up_rectangles,
                            product_min_down_rectangles,
                            product_max_up_rectangles,
                            product_max_down_rectangles,
                            set_count_up_rectangles,
                            set_count_down_rectangles,
                            time_limit_up_rectangles,
                            time_limit_down_rectangles
                        );

                    }
                    
                    // Else, if the min sum sign arrow was clicked, the sign is changed.
                    else if (
                        sum_min_sign_clicked && (
                            sum_min_up_rectangles[0].contains(event.click_position())
                            || sum_min_down_rectangles[0].contains(event.click_position())
                        )
                    ) {
                        sum_range[0] *= -1;
                    }
                    
                    // Else, if the max sum sign arrow was clicked, the sign is changed.
                    else if (
                        sum_max_sign_clicked && (
                            sum_max_up_rectangles[0].contains(event.click_position())
                            || sum_max_down_rectangles[0].contains(event.click_position())
                        )
                    ) {
                        sum_range[1] *= -1;
                    }
                    
                    // Else, if the min product sign arrow was clicked, the sign is changed.
                    else if (
                        product_min_sign_clicked && (
                            product_min_up_rectangles[0].contains(event.click_position())
                            || product_min_down_rectangles[0].contains(event.click_position())
                        )
                    ) {
                        product_range[0] *= -1;
                    }
                    
                    // Else, if the max product sign arrow was clicked, the sign is changed.
                    else if (
                        product_max_sign_clicked && (
                            product_max_up_rectangles[0].contains(event.click_position())
                            || product_max_down_rectangles[0].contains(event.click_position())
                        )
                    ) {
                        product_range[1] *= -1;
                    }
                    
                    // Else, if back was clicked, the main menu is returned to.
                    else if (back_clicked && back.get_rectangle().contains(event.click_position())) {
                        end = true;
                    }
                    
                    // Else, the value arrows are checked.
                    else {
                        bool done = false;
                        
                        // Sum range value modifiers.
                        for (int i = SUM_DIGITS, change = 1; !done && i > 0; i--, change *= 10) {
                            if (sum_min_up_rectangles[i].contains(event.click_position())) {
                                sum_range[0] += change;
                                done = true;
                            }
                            
                            else if (sum_min_down_rectangles[i].contains(event.click_position())) {
                                sum_range[0] -= change;
                                done = true;
                            }
                            
                            else if (sum_max_up_rectangles[i].contains(event.click_position())) {
                                sum_range[1] += change;
                                done = true;
                            }
                            
                            else if (sum_max_down_rectangles[i].contains(event.click_position())) {
                                sum_range[1] -= change;
                                done = true;
                            }
                        }
                        
                        // Product range value modifiers.
                        for (int i = PRODUCT_DIGITS, change = 1; !done && i > 0; i--, change *= 10) {
                            if (product_min_up_rectangles[i].contains(event.click_position())) {
                                product_range[0] += change;
                                done = true;
                            }
                            
                            else if (product_min_down_rectangles[i].contains(event.click_position())) {
                                product_range[0] -= change;
                                done = true;
                            }
                            
                            else if (product_max_up_rectangles[i].contains(event.click_position())) {
                                product_range[1] += change;
                                done = true;
                            }
                            
                            else if (product_max_down_rectangles[i].contains(event.click_position())) {
                                product_range[1] -= change;
                                done = true;
                            }
                        }
                        
                        // Question set count value modifiers.
                        for (int i = SET_DIGITS - 1, change = 1; !done && i >= 0; i--, change *= 10) {
                            if (set_count_up_rectangles[i].contains(event.click_position())) {
                                set_count += change;
                                done = true;
                            }
                            
                            else if (set_count_down_rectangles[i].contains(event.click_position())) {
                                set_count -= change;
                                done = true;
                            }
                        }
                        
                        // Time per question value modifiers.
                        for (int i = TIME_DIGITS - 1, change = 1; !done && i >= 0; i--, change *= 10) {
                            if (time_limit_up_rectangles[i].contains(event.click_position())) {
                                time_limit += change;
                                done = true;
                            }
                            
                            else if (time_limit_down_rectangles[i].contains(event.click_position())) {
                                time_limit -= change;
                                done = true;
                            }
                        }
                    }
                    
                    // The click statuses are reset.
                    begin_clicked = false;
                    back_clicked = false;
                    sum_min_sign_clicked = false;
                    sum_max_sign_clicked = false;
                    product_min_sign_clicked = false;
                    product_max_sign_clicked = false;
                    
                    break;
                //}
                
                // Keyboard input.
                case Event::KEY_RELEASE: //{
                    // The quiz begins.
                    if (event.key() == SUBMIT_KEY) {
                        if (test(
                            display,
                            background,
                            back,
                            renderer,
                            sum_range,
                            product_range,
                            set_count,
                            time_limit
                        )) {
                            return true;
                        }
                        
                        // The sprites are resized.
                        resize_configure(
                            display,
                            background,
                            sum,
                            product,
                            set,
                            time,
                            to,
                            back,
                            begin,
                            up_arrow,
                            down_arrow,
                            sum_min_up_rectangles,
                            sum_min_down_rectangles,
                            sum_max_up_rectangles,
                            sum_max_down_rectangles,
                            product_min_up_rectangles,
                            product_min_down_rectangles,
                            product_max_up_rectangles,
                            product_max_down_rectangles,
                            set_count_up_rectangles,
                            set_count_down_rectangles,
                            time_limit_up_rectangles,
                            time_limit_down_rectangles
                        );
                    }
                    
                    // The main menu is returned to.
                    else if (event.key() == QUIT_KEY) {
                        end = true;
                    }
                    
                    break;
                //}
            }
        }
	}
    
    return false;
}
//}

// Main menu
//{
/**
 * Shows info about this program on the screen and halts thread functionality.
 */
bool display_info(Display& display, const Sprite& snapshot) noexcept {
	// The info screen.
	Button info(
        Sprite(INFO_SCREEN_SOURCE, display, INFO_SCREEN_WIDTH, INFO_SCREEN_HEIGHT),
		display, INFO_SCREEN_X, INFO_SCREEN_Y
	);
	
    // Handles events.
    Event event;
    
    // True when the info screen should be closed.
    bool end = false;
    
    // Loop to render and handle input.
    while (!end) {
        // The information is displayed.
        info.blit_to(display);
        display.update();
        
        // Check for an event.
        while (!end && event.poll()) {
            // Handle the event.
            switch (event.type()) {
                // Shut down.
                case Event::TERMINATE: //{
                    return true;
                //}
                
                // Resize (and rotation) handling.
                case Event::RESIZE: //{
                    // The display is reinitialised.
                    display.resize(event.window_width(), event.window_height());
                    
                    // The info screen is resized.
                    info = Button(
                        Sprite(INFO_SCREEN_SOURCE, display, INFO_SCREEN_WIDTH, INFO_SCREEN_HEIGHT),
                        display, INFO_SCREEN_X, INFO_SCREEN_Y
                    );
                    
                    // The display is returned to its former state.
                    display.blit(snapshot);
                    
                    break;
                //}
                
                // A click (or touch) or key press exits the info screen.
                case Event::LEFT_UNCLICK:
                case Event::KEY_RELEASE: //{
                    end = true;
                    break;
                //}
            }
        }
    }
    
    // The program should not shut down.
    return false;
}

/**
 * Resizes the main menu's sprites.
 */
void resize_main(
    const Sprite& display,
    Button& background,
    Button& title,
    Button& copyright,
    Button& start,
    Button& info,
    Button& quit
) noexcept {
    background = Button(Sprite(BACKGROUND_SOURCE, display.width(), display.height()));
    title = Button(Sprite(TITLE_SOURCE, display, TITLE_WIDTH, TITLE_HEIGHT), display, TITLE_X, TITLE_Y);
    copyright = Button(
        Sprite(COPYRIGHT_SOURCE, display, COPYRIGHT_WIDTH, COPYRIGHT_HEIGHT),
        display, COPYRIGHT_X, COPYRIGHT_Y
    );
    start = Button(Sprite(START_SOURCE, display, START_WIDTH, START_HEIGHT), display, START_X, START_Y);
    info = Button(Sprite(INFO_SOURCE, display, INFO_WIDTH, INFO_HEIGHT), display, INFO_X, INFO_Y);
    quit = Button(Sprite(QUIT_SOURCE, display, QUIT_WIDTH, QUIT_HEIGHT), display, QUIT_X, QUIT_Y);
}

/**
 * An automatic mental maths quizzer with customisable difficulty and length.
 */
int main(int arcg, char** argv) {
	// SDL is initialised for video and audio.
	System::initialise(System::VIDEO | System::AUDIO);
    
    // The version of this program and the version of
    //   the SDL and Net Utilities library are displayed.
    std::string version_string = System::version(VERSION);
    std::cout
        << "\nAutoSchool: Mathematics by Chigozie Agomo.\nVersion: "
        << version_string
        << "\n\nPowered by:\n"
        << System::info()
        << "\n\n"
    ;
	
	// Scope to ensure that the objects are destroyed before SDL is terminated.
	{
		// The display is initialised.
		Display display;
        
        // The main menu sprites are initialised.
        Button background(Sprite(BACKGROUND_SOURCE, display.width(), display.height()));
        Button title(Sprite(TITLE_SOURCE, display, TITLE_WIDTH, TITLE_HEIGHT), display, TITLE_X, TITLE_Y);
        Button copyright(
            Sprite(COPYRIGHT_SOURCE, display, COPYRIGHT_WIDTH, COPYRIGHT_HEIGHT),
            display, COPYRIGHT_X, COPYRIGHT_Y
        );
        Button start(Sprite(START_SOURCE, display, START_WIDTH, START_HEIGHT), display, START_X, START_Y);
		Button info(Sprite(INFO_SOURCE, display, INFO_WIDTH, INFO_HEIGHT), display, INFO_X, INFO_Y);
		Button quit(Sprite(QUIT_SOURCE, display, QUIT_WIDTH, QUIT_HEIGHT), display, QUIT_X, QUIT_Y);
		
		// The music is loaded and queued in another thread until the program ends.
		AudioThread audio(MUSIC_SOURCE, MUSIC_LENGTH);
        
        // Handles events.
        Event event;
		
		// Set to true when the program should end.
		bool end = false;
        
        // True if the corresponding button was clicked.
        bool start_clicked = false;
        bool info_clicked = false;
        bool quit_clicked = false;
		
		// Main menu loop.
		while (!end) {
            // The menu's sprites are displayed.
            background.blit_to(display);
            title.blit_to(display);
			copyright.blit_to(display);
			start.blit_to(display);
			info.blit_to(display);
			quit.blit_to(display);
			display.update();
            
            // Check for an event.
            while (!end && event.poll()) {
                // Handle the event.
                switch (event.type()) {
                    // End the game.
                    case Event::TERMINATE: //{
                        end = true;
                        break;
                    //}
                    
                    // Resize (and rotation) handling.
                    case Event::RESIZE: //{
                        // The display is resized.
                        display.resize(event.window_width(), event.window_height());
                        
                        // The sprites are resized.
                        resize_main(display, background, title, copyright, start, info, quit);
                        
                        break;
                    //}
                    
                    // Mouse clicks (and screen touches).
                    case Event::LEFT_CLICK: //{
                        if (start.get_rectangle().contains(event.click_position())) {
                            start_clicked = true;
                        }
                        
                        else if (info.get_rectangle().contains(event.click_position())) {
                            info_clicked = true;
                        }
                        
                        else if (quit.get_rectangle().contains(event.click_position())) {
                            quit_clicked = true;
                        }
                        
                        break;
                    //}
                    
                    // Mouse (and screen) releases.
                    case Event::LEFT_UNCLICK: //{
                        // If start was clicked, the configuration menu is advanced to.
                        if (start_clicked && start.get_rectangle().contains(event.click_position())) {
                            end = configure(display, background);
                        
                            // The sprites are resized.
                            resize_main(display, background, title, copyright, start, info, quit);
                        }
                        
                        // Else, if info was clicked, the info menu is displayed.
                        else if (info_clicked && info.get_rectangle().contains(event.click_position())) {
                            // The display's current appearance is stored.
                            Sprite snapshot(display);
                            end = display_info(display, snapshot);
                        
                            // The sprites are resized.
                            resize_main(display, background, title, copyright, start, info, quit);
                        }
                        
                        // Else, if quit was clicked, the program ends.
                        else if (quit_clicked && quit.get_rectangle().contains(event.click_position())) {
                            end = true;
                        }
                        
                        // The click statuses are reset.
                        start_clicked = false;
                        info_clicked = false;
                        quit_clicked = false;
                        
                        break;
                    //}
                    
                    // Keyboard input.
                    case Event::KEY_RELEASE: //{
                        // The configuration menu is advanced to.
                        if (event.key() == SUBMIT_KEY) {
                            end = configure(display, background);
                        
                            // The sprites are resized.
                            resize_main(display, background, title, copyright, start, info, quit);
                        }
                        
                        // The program ends.
                        else if (event.key() == QUIT_KEY) {
                            end = true;
                        }
                        
                        break;
                    //}
                }
            }
        }
	}
	
    // SDL is shut down.
	System::terminate();
	return 0;
}
//}

/* CHANGELOG:
     v2:
        Use modern sdlandnet and reverse the changelog's order.
	 v-1.0.4:
	   Rearranged the position of the question and the buttons.
	   The results display now reloads the operator sprites.
	 v-1.0.3:
	   Changes to accomodate mobile devices (onscreen buttons).
	 v1.0.3:
	   Results arrows are no longer displayed if they take no effect.
	   The .dll files were updated.
	 v1.0.2.1:
	   Now uses sdlandnet.hpp v1.0.0.1 (instead of v0.8.5).
	 v1.0.2:
	   Renamed v1.1 to v1.0.1
	   Enter can now advance the page in the menus.
	   Added a version message that is printed to standard output
	     at the start of the program.
     v1.0.1:
	   Added keybindings for the results page.
     v1:
       First version.
 */