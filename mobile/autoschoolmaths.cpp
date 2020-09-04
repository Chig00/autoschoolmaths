#include <iostream>
#include <vector>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "sdlandnet.hpp"

// Constants
//{
// The current version.
constexpr int VERSION[] = {-1, 0, 4, 0};
constexpr int VERSION_LENGTH = 4;

// The number of different types of question.
constexpr int QUESTION_TYPES = 4;

// The number of different types of question outcome.
constexpr int OUTCOME_TYPES = 3;

// The default test configuration.
constexpr int SUM_MIN = 0;
constexpr int SUM_MAX = 20;
constexpr int PRODUCT_MIN = 0;
constexpr int PRODUCT_MAX = 12;
constexpr int SET_COUNT = 3;
constexpr int TIME_LIMIT = 20;

// Test configuration constants.
constexpr int SUM_DIGITS = 3;
constexpr int PRODUCT_DIGITS = 2;
constexpr int SET_DIGITS = 2;
constexpr int TIME_DIGITS = 3;
constexpr int SUM_RANGE[] = {-999, 999};
constexpr int PRODUCT_RANGE[] = {-99, 99};
constexpr int SET_RANGE[] = {1, 99};
constexpr int TIME_RANGE[] = {0, 999};

// The keybindings values.
constexpr int QUIT_KEY = Events::ESCAPE;
constexpr int SUBMIT_KEY = Events::ENTER;
constexpr int BACK_KEY = Events::BACKSPACE;
constexpr int MINUS_KEY = Events::MINUS;
constexpr int PREVIOUS_KEY = Events::LEFT;
constexpr int NEXT_KEY = Events::RIGHT;
constexpr const int* NUMBER_KEYS = Events::NUMBERS;

// The maximum length of an attempt at an answer.
constexpr int MAX_ATTEMPT = 5;

// Position and dimensions of the title.
constexpr double TITLE_WIDTH = 0.75;
constexpr double TITLE_HEIGHT = 0.4;
constexpr double TITLE_X = 0.5;
constexpr double TITLE_Y = 0.25;

// Position and dimensions of the copyright button.
constexpr double COPYRIGHT_WIDTH = 0.3;
constexpr double COPYRIGHT_HEIGHT = 0.0875;
constexpr double COPYRIGHT_X = 0.1625;
constexpr double COPYRIGHT_Y = 0.9375;

// Position and dimensions of the start button.
constexpr double START_WIDTH = 0.2;
constexpr double START_HEIGHT = 0.125;
constexpr double START_X = 0.5;
constexpr double START_Y = 0.625;

// Position and dimensions of the info button.
constexpr double INFO_WIDTH = START_WIDTH;
constexpr double INFO_HEIGHT = START_HEIGHT;
constexpr double INFO_X = START_X;
constexpr double INFO_Y = 0.825;

// Position and dimensions of the quit button.
constexpr double QUIT_WIDTH = 0.125;
constexpr double QUIT_HEIGHT = 0.0875;
constexpr double QUIT_X = 0.925;
constexpr double QUIT_Y = 0.95;

// Position and dimensions of the info screen.
constexpr double INFO_SCREEN_WIDTH = 0.9;
constexpr double INFO_SCREEN_HEIGHT = 0.75;
constexpr double INFO_SCREEN_X = 0.5;
constexpr double INFO_SCREEN_Y = 0.45;

// Position and dimensions of the sum range prompt.
constexpr double SUM_WIDTH = 0.4;
constexpr double SUM_HEIGHT = 0.1375;
constexpr double SUM_X = 0.225;
constexpr double SUM_Y = 0.1;

// Position and dimensions of the product range prompt.
constexpr double PRODUCT_WIDTH = SUM_WIDTH;
constexpr double PRODUCT_HEIGHT = SUM_HEIGHT;
constexpr double PRODUCT_X = SUM_X;
constexpr double PRODUCT_Y = 0.325;

// Position and dimensions of the question set count prompt.
constexpr double SET_WIDTH = PRODUCT_WIDTH;
constexpr double SET_HEIGHT = PRODUCT_HEIGHT;
constexpr double SET_X = PRODUCT_X;
constexpr double SET_Y = 0.55;

// Position and dimensions of the question time prompt.
constexpr double TIME_WIDTH = SET_WIDTH;
constexpr double TIME_HEIGHT = SET_HEIGHT;
constexpr double TIME_X = SET_X;
constexpr double TIME_Y = 0.775;

// Position and dimensions of the to button.
constexpr double TO_WIDTH = 0.05;
constexpr double TO_HEIGHT = 0.075;
constexpr double TO_X[] = {0.7, 0.7};
constexpr double TO_Y[] = {SUM_Y, PRODUCT_Y};

// Position and dimensions of the back button.
constexpr double BACK_WIDTH = QUIT_WIDTH;
constexpr double BACK_HEIGHT = QUIT_HEIGHT;
constexpr double BACK_X = 1 - QUIT_X;
constexpr double BACK_Y = QUIT_Y;

// Position and dimensions of the begin button.
constexpr double BEGIN_WIDTH = BACK_WIDTH;
constexpr double BEGIN_HEIGHT = BACK_HEIGHT;
constexpr double BEGIN_X = 1 - BACK_X;
constexpr double BEGIN_Y = BACK_Y;

// Position and dimensions of the up arrow button.
constexpr double UP_WIDTH = 0.04;
constexpr double UP_HEIGHT = 0.03;

// Position and dimensions of the down arrow button.
constexpr double DOWN_WIDTH = UP_WIDTH;
constexpr double DOWN_HEIGHT = UP_HEIGHT;

// Position and dimensions of the minimum sum value.
constexpr double SUM_MIN_WIDTH = DOWN_WIDTH;
constexpr double SUM_MIN_HEIGHT = TO_HEIGHT;
constexpr double SUM_MIN_X = 0.55;
constexpr double SUM_MIN_Y = TO_Y[0];

// Position and dimensions of the maximum sum value.
constexpr double SUM_MAX_WIDTH = SUM_MIN_WIDTH;
constexpr double SUM_MAX_HEIGHT = SUM_MIN_HEIGHT;
constexpr double SUM_MAX_X = 2 * TO_X[0] - SUM_MIN_X;
constexpr double SUM_MAX_Y = SUM_MIN_Y;

// Position and dimensions of the minimum product value.
constexpr double PRODUCT_MIN_WIDTH = SUM_MAX_WIDTH;
constexpr double PRODUCT_MIN_HEIGHT = SUM_MAX_HEIGHT;
constexpr double PRODUCT_MIN_X = SUM_MIN_X;
constexpr double PRODUCT_MIN_Y = TO_Y[1];

// Position and dimensions of the maximum product value.
constexpr double PRODUCT_MAX_WIDTH = PRODUCT_MIN_WIDTH;
constexpr double PRODUCT_MAX_HEIGHT = PRODUCT_MIN_HEIGHT;
constexpr double PRODUCT_MAX_X = 2 * TO_X[1] - PRODUCT_MIN_X;
constexpr double PRODUCT_MAX_Y = PRODUCT_MIN_Y;

// Position and dimensions of the question set count value.
constexpr double SET_COUNT_WIDTH = PRODUCT_MAX_WIDTH;
constexpr double SET_COUNT_HEIGHT = PRODUCT_MAX_HEIGHT;
constexpr double SET_COUNT_X = TO_X[1];
constexpr double SET_COUNT_Y = SET_Y;

// Position and dimensions of the time limit value.
constexpr double TIME_LIMIT_WIDTH = SET_COUNT_WIDTH;
constexpr double TIME_LIMIT_HEIGHT = SET_COUNT_HEIGHT;
constexpr double TIME_LIMIT_X = SET_COUNT_X;
constexpr double TIME_LIMIT_Y = TIME_Y;

// Position and dimensions of the operands.
constexpr double OPERAND_WIDTH = 0.05;
constexpr double OPERAND_HEIGHT = 0.125;
constexpr double OPERAND_X[] = {0.1125, 0.45};
constexpr double OPERAND_Y = 0.3;

// Position and dimensions of the operators.
constexpr double OPERATOR_WIDTH = 0.075;
constexpr double OPERATOR_HEIGHT = 0.0875;
constexpr double OPERATOR_X = (OPERAND_X[0] + OPERAND_X[1]) / 2;
constexpr double OPERATOR_Y = OPERAND_Y;

// Position of the equals sign.
constexpr double EQUALS_X = 2 * OPERAND_X[1] - OPERATOR_X;
constexpr double EQUALS_Y = OPERATOR_Y;

// Position and dimensions of the attempted answer.
constexpr double ATTEMPT_WIDTH = OPERAND_WIDTH;
constexpr double ATTEMPT_HEIGHT = OPERAND_HEIGHT;
constexpr double ATTEMPT_X = 2 * EQUALS_X - OPERAND_X[1];
constexpr double ATTEMPT_Y = OPERAND_Y;

// Position and dimensions of the timer.
constexpr double TIMER_WIDTH = 0.05;
constexpr double TIMER_HEIGHT = 0.5;
constexpr double TIMER_X = 0.95;
constexpr double TIMER_Y = 0.3;

// Position and dimensions of the results.
constexpr double RESULTS_WIDTH = 0.3;
constexpr double RESULTS_HEIGHT = TIME_HEIGHT;
constexpr double RESULTS_X = 0.1625;
constexpr double RESULTS_Y = 0.1;

// Position and dimensions of the slash.
constexpr double SLASH_WIDTH = 0.0375;
constexpr double SLASH_HEIGHT = RESULTS_HEIGHT;
constexpr double SLASH_X = 0.5;
constexpr double SLASH_Y = RESULTS_Y;

// Position and dimensions of the percent sign.
constexpr double PERCENT_WIDTH = 0.075;
constexpr double PERCENT_HEIGHT = SLASH_HEIGHT;
constexpr double PERCENT_X = 0.925;
constexpr double PERCENT_Y = SLASH_Y;

// Positions and dimensions of the left arrow button.
constexpr double LEFT_WIDTH = 0.025;
constexpr double LEFT_HEIGHT = 0.1;
constexpr double LEFT_X = 0.025;
constexpr double LEFT_Y = 0.5;

// Positions and dimensions of the right arrow button.
constexpr double RIGHT_WIDTH = LEFT_WIDTH;
constexpr double RIGHT_HEIGHT = LEFT_HEIGHT;
constexpr double RIGHT_X = 1 - LEFT_X;
constexpr double RIGHT_Y = LEFT_Y;

// Positions and dimensions of the score.
constexpr double SCORE_WIDTH = 0.0375;
constexpr double SCORE_HEIGHT = PERCENT_HEIGHT;
constexpr double SCORE_X = 0.4;
constexpr double SCORE_Y = PERCENT_Y;

// Positions and dimensions of the total.
constexpr double TOTAL_WIDTH = SCORE_WIDTH;
constexpr double TOTAL_HEIGHT = SCORE_HEIGHT;
constexpr double TOTAL_X = 2 * SLASH_X - SCORE_X;
constexpr double TOTAL_Y = SCORE_Y;

// Position and dimensions of the percentage.
constexpr double PERCENTAGE_WIDTH = TOTAL_WIDTH;
constexpr double PERCENTAGE_HEIGHT = TOTAL_HEIGHT;
constexpr double PERCENTAGE_X = 0.8;
constexpr double PERCENTAGE_Y = TOTAL_Y;

// Postion and dimensions of the results questions.
constexpr double QUESTION_WIDTH[] = {0.9, 0.03, 0.05};
constexpr double QUESTION_HEIGHT = 0.1;
constexpr double QUESTION_X[] = {0.5, 0.1, 0.2375, 0.375, 0.5, 0.625, 0.7625, 0.9};
constexpr double QUESTION_Y[] = {0.3, 0.433, 0.567, 0.7};

// Positions and dimensions of the mobile number buttons.
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

// Position and dimensions of the mobile negative sign button.
constexpr double MINUS_WIDTH = NUMBER_WIDTH;
constexpr double MINUS_HEIGHT = MINUS_WIDTH;
constexpr double MINUS_X = NUMBER_X[0] - MINUS_WIDTH;
constexpr double MINUS_Y = NUMBER_Y;

// Position and dimensions of the next button.
constexpr double NEXT_WIDTH = BEGIN_WIDTH;
constexpr double NEXT_HEIGHT = BEGIN_HEIGHT;
constexpr double NEXT_X = BEGIN_X;
constexpr double NEXT_Y = BEGIN_Y;

// File locations of the sprites.
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

/**
 * A specialised renderer for rendering signed integers.
 */
class SignedRenderer: private Renderer<NUMBERS> {
	public:
		/**
		 * Takes sources for the numbers and the minus sign.
		 * The sources should be passed in this order: 0 to 9, then "-".
		 */
		SignedRenderer(
			const std::array<std::string, NUMBERS>& sources,
			const std::string& minus_source
		):
			Renderer(sources, true),
			minus_sign(minus_source)
		{}
		
		/**
		 * Returns the number string given as a sprite with
		 *   a white backgrond.
		 */
		Sprite render(const std::string& number_string, int width, int height) const {
			// The numbers are rendered using the superclass.
			Sprite rendering = Renderer::render(number_string, width, height);
			
			// The minus sign is added (if applicable).
			if (number_string.length()) {
				if (number_string[0] == '-') {
					Sprite temporary(width, height);
					temporary.blit(minus_sign);
					rendering.blit(temporary, 0, 0);
				}
				
				else if (number_string[0] == ' ') {
					Sprite temporary(width, height);
					temporary.fill(WHITE);
					rendering.blit(temporary, 0, 0);
				}
			}
			
			// The sprite is returned.
			return rendering;
		}
	
	private:
		Sprite minus_sign; // The sprite for a minus sign.
};

/**
 * Returns a string representation of a signed integer.
 * The first character is either a minus sign or space.
 * The digits parameter represents how many digits from
 *   the value are taken (from smallest to largest).
 */
std::string signed_string(int value, int digits) {
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
std::string unsigned_string(int value, int digits) {
	std::string string;
	string.resize(digits);
	
	for (int i = 0; i < digits; i++) {
		string[digits - 1 - i] = '0' + value % 10;
		value /= 10;
	}
	
	return string;
}

int get_digits(int value) {
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
			std::mt19937& generator,
			std::uniform_int_distribution<int>& sum_distribution,
			std::uniform_int_distribution<int>& product_distribution,
			int op
		) {
			switch (op) {
				case 0:
					operands[0] = sum_distribution(generator);
					operands[1] = sum_distribution(generator);
					answer = operands[0] + operands[1];
					break;
					
				case 1:
					answer = sum_distribution(generator);
					operands[1] = sum_distribution(generator);
					operands[0] = operands[1] + answer;
					break;
					
				case 2:
					operands[0] = product_distribution(generator);
					operands[1] = product_distribution(generator);
					answer = operands[0] * operands[1];
					break;
					
				case 3:
					answer = product_distribution(generator);
					operands[1] = product_distribution(generator);
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
		bool question(
			Display& display,
			const Sprite& background,
			const Button& back_button,
			const SignedRenderer& renderer,
			const std::array<std::unique_ptr<Sprite>, QUESTION_TYPES + 1>& operators,
			int time_limit
		) {
			// The components of the display are extracted.
			Sprite& display_sprite = display.get_sprite();
			int display_width = display_sprite.get_width();
			int display_height = display_sprite.get_height();
			
			// The timer's sprite is set up.
			Sprite timer(
				TIMER_WIDTH * display_width,
				TIMER_HEIGHT * display_height
			);
			
			// The user's attempt at the answer;
			std::string attempt_string;
			
			// The timer is set up.
			int remaining_time = time_limit;
			double last_tick = Timer::time();
			
			// True if the testing should cease.
			bool finished = false;
			// True when the questioning ends.
			bool end = false;
			
			// A next button for use on mobile devices.
			Button next_button(
				std::make_unique<Sprite>(
					NEXT_SOURCE,
					NEXT_WIDTH * display_width,
					NEXT_HEIGHT * display_height
				),
				display_sprite,
				NEXT_X,
				NEXT_Y
			);
			
			// A minus button for use on mobile devices.
			Button minus_button(
				std::make_unique<Sprite>(
					MINUS_SOURCE,
					MINUS_WIDTH * display_width,
					MINUS_HEIGHT * display_height
				),
				display_sprite,
				MINUS_X,
				MINUS_Y
			);
			
			// A vector of number buttons for use on mobile devices.
			std::vector<Button> number_buttons;
			
			for (int i = 0; i < 10; ++i) {
				number_buttons.push_back(
					Button(
						std::make_unique<Sprite>(
							NUMBER_SOURCES[i],
							NUMBER_WIDTH * display_width,
							NUMBER_HEIGHT * display_height
						),
						display_sprite,
						NUMBER_X[i],
						NUMBER_Y
					)
				);
			}
			
			// Loops until the questioning ends.
			while (!end) {
				// The timer's colour is set depending on the remaining time.
				if (time_limit) {
					timer.fill(BLACK);
				}
				
				else {
					timer.fill(GREEN);
				}
				
				// If time remains, the timer has a portion of its sprite
				//   filled to represent the remaining time.
				if (remaining_time) {
					// The rectangle to be filled in is centred on the timer.
					int width = timer.get_width();
					int height = timer.get_height();
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
					
					// The timer is filled in according to
					//   the bounds of the rectangle.
					// The colour goes from green at full time
					//   to red when almost out of time.
					timer.fill(
						time_rectangle,
						0xff - new_height * 0xff / height,
						new_height * 0xff / height,
						0
					);
				}
				
				// The display is blitted to.
				display_sprite.blit(background, 0, 0);
				display_sprite.blit(timer, TIMER_X, TIMER_Y);
				display_sprite.blit(*operators[operation], OPERATOR_X, OPERATOR_Y);
				display_sprite.blit(*operators[QUESTION_TYPES], EQUALS_X, EQUALS_Y);
				back_button.blit_to(display_sprite);
				next_button.blit_to(display_sprite);
				minus_button.blit_to(display_sprite);
				
				for (int i = 0; i < 10; ++i) {
					number_buttons[i].blit_to(display_sprite);
				}
				
				// The operands and attempted answer are blitted to the display.
				display_sprite.blit(
					renderer.render(
						operands[0] < 0
							? signed_string(operands[0], get_digits(operands[0]))
							: unsigned_string(operands[0], get_digits(operands[0]))
						,
						OPERAND_WIDTH * display_width,
						OPERAND_HEIGHT * display_height
					),
					OPERAND_X[0],
					OPERAND_Y
				);
				display_sprite.blit(
					renderer.render(
						operands[1] < 0
							? signed_string(operands[1], get_digits(operands[1]))
							: unsigned_string(operands[1], get_digits(operands[1]))
						,
						OPERAND_WIDTH * display_width,
						OPERAND_HEIGHT * display_height
					),
					OPERAND_X[1],
					OPERAND_Y
				);
				display_sprite.blit(
					renderer.render(
						attempt_string,
						ATTEMPT_WIDTH * display_width,
						ATTEMPT_HEIGHT * display_height
					),
					ATTEMPT_X,
					ATTEMPT_Y
				);
				
				// The display is updated.
				display.update();
				
				// Loop for input.
				while (true) {
					int length = attempt_string.length();
					
					// If a second has elapsed since the last tick, the remaining
					//   time is decremented and the last_tick is incremented.
					if (remaining_time && Timer::time() >= last_tick + 1) {
						remaining_time -= 1;
						last_tick += 1;
						break;
					}
					
					Point mouse;
					bool clicked = Events::unclick(Events::LEFT_CLICK, mouse);
					
					// Clicking the back button end the testing.
					// Pressing the quit key ends the testing.
					if (
						clicked
						&& back_button.get_rectangle().contains(mouse)
						&& !length
						|| Events::unpress(QUIT_KEY)
					) {
						finished = true;
						end = true;
						break;
					}
					
					// Pressing enter will submit the answer.
					// Submissions requires a number to have been entered.
					else if (
						clicked
						&& next_button.get_rectangle().contains(mouse)
						|| Events::unpress(SUBMIT_KEY)
					) {
						bool valid = false;
						
						for (int i = 0; i < length; i++) {
							if ('0' <= attempt_string[i] && attempt_string[i] <= '9') {
								valid = true;
								break;
							}
						}
						
						if (valid) {
							end = true;
							break;
						}
					}
					
					// If the string is empty, one can make the answer negative.
					else if (
						!length
						&& (
							clicked
							&& minus_button.get_rectangle().contains(mouse)
							|| Events::unpress(MINUS_KEY)
						)
					) {
						attempt_string += '-';
						break;
					}
					
					// If the string isn't empty, one can remove
					//   the last character of their answer.
					else if (
						length
						&& (
							clicked
							&& back_button.get_rectangle().contains(mouse)
							|| Events::unpress(BACK_KEY)
						)
					) {
						attempt_string.pop_back();
						break;
					}
					
					// The number buttons are checked.
					// The number button pressed appends that digit to the string.
					// The string cannot exceed a specific length.
					else if (length < MAX_ATTEMPT) {
						bool pressed = false;
						
						for (int i = 0; i < NUMBERS; i++) {
							if (
								clicked
								&& number_buttons[i].get_rectangle().contains(mouse)
								|| Events::unpress(NUMBER_KEYS[i])
							) {
								attempt_string += '0' + i;
								pressed = true;
								break;
							}
						}
						
						if (pressed) {
							break;
						}
					}
					
					Events::update();
				}
			}
			
			// If there was a time limit, but no time remains,
			//   the question is marked as late.
			late = time_limit && !remaining_time;
			
			if (!finished) {
				// The attempted answer is stored as an integer.
				attempt = std::stoi(attempt_string);
			}
			
			return finished;
		}
		
		/**
		 * Returns true if the attempt is equal to the actual answer
		 *   and the question wasn't answered late.
		 */
		int correct() {
			int outcome = 0;
			
			if (answer == attempt) {
				outcome++;
				
				if (!late) {
					outcome++;
				}
			}
			
			return outcome;
		}
		
		/**
		 * Returns a sprite representation of the question.
		 */
		Sprite get_sprite(
			const Display& display,
			const SignedRenderer& renderer,
			const std::array<std::unique_ptr<Sprite>, QUESTION_TYPES + 1>& operators,
			const std::array<std::unique_ptr<Sprite>, OUTCOME_TYPES>& outcomes
		) {
			// The components of the display are extracted.
			const Sprite& display_sprite = display.get_sprite();
			int display_width = display_sprite.get_width();
			int display_height = display_sprite.get_height();
			
			// The sprite to be returned.
			Sprite sprite(
				QUESTION_WIDTH[0] * display_width,
				QUESTION_HEIGHT * display_height
			);
			
			// The dimensions of the sprite are extracted.
			int width = sprite.get_width();
			int height = sprite.get_height();
			
			// The first operand is blitted.
			sprite.blit(
				renderer.render(
					operands[0] < 0
						? signed_string(operands[0], get_digits(operands[0]))
						: unsigned_string(operands[0], get_digits(operands[0]))
					,
					QUESTION_WIDTH[1] * width,
					height
				),
				QUESTION_X[1],
				0.5
			);
			
			// The second operand is blitted.
			sprite.blit(
				renderer.render(
					operands[1] < 0
						? signed_string(operands[1], get_digits(operands[1]))
						: unsigned_string(operands[1], get_digits(operands[1]))
					,
					QUESTION_WIDTH[1] * width,
					height
				),
				QUESTION_X[3],
				0.5
			);
			
			// The attempt at an answer is blitted.
			sprite.blit(
				renderer.render(
					attempt < 0
						? signed_string(attempt, get_digits(attempt))
						: unsigned_string(attempt, get_digits(attempt))
					,
					QUESTION_WIDTH[1] * width,
					height
				),
				QUESTION_X[5],
				0.5
			);
			
			// The actual answer is blitted if it was wrong.
			if (attempt != answer) {
				sprite.blit(
					renderer.render(
						answer < 0
							? signed_string(answer, get_digits(answer))
							: unsigned_string(answer, get_digits(answer))
						,
						QUESTION_WIDTH[1] * width,
						height
					),
					QUESTION_X[7],
					0.5
				);
			}
			
			// The operator is blitted.
			Sprite operator_(
				OPERATOR_SOURCES[operation],
				QUESTION_WIDTH[2] * width,
				height
			);
			sprite.blit(operator_, QUESTION_X[2], 0.5);
			
			// The equals sign is blitted.
			Sprite equals(
				OPERATOR_SOURCES[4],
				QUESTION_WIDTH[2] * width,
				height
			);
			sprite.blit(equals, QUESTION_X[4], 0.5);
			
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
		std::array<int, 2> operands; // The two operands in the operation.
		int answer;                  // The answer to the operation.
		int operation;               // The operation code (+-*/).
		int attempt;                 // The user's attempt at an answer.
		bool late;                   // True if the user answered too late.
};

/**
 * Continuously queues audio while the audio is to be played.
 */
int queue_audio(void* data) {
	Audio* audio = static_cast<Audio*>(data);
	
	while (!audio->pause_check()) {
		audio->queue();
	}
	
	return 0;
}

/**
 * Opens the support link in the default browser.
 */
void support() {
	System::command(std::string(SUPPORT_COMMAND) + SUPPORT_LINK);
}

/**
 * Shows info about this program on the screen and halts thread functionality,
 *   until the quit key is pressed or the screen is clicked where the info is
 *   not being displayed.
 */
void display_info(Display& display) {
	// The display's components are stored.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The info screen.
	Button info(
		std::make_unique<Sprite>(
			INFO_SCREEN_SOURCE,
			INFO_SCREEN_WIDTH * display_width,
			INFO_SCREEN_HEIGHT * display_height
		),
		display_sprite,
		INFO_SCREEN_X,
		INFO_SCREEN_Y
	);
	
	// The information is displayed.
	info.blit_to(display_sprite);
	display.update();
	
	// Waits until the quit key is pressed and released.
	while (!Events::unpress(QUIT_KEY)) {
		// If the area outside of the information is clicked, the wait ends.
		if (Events::click(Events::LEFT_CLICK)) {
			if (!info.get_rectangle().unclick(Events::LEFT_CLICK)) {
				break;
			}
		}
		
		Events::update();
	}
}

/**
 * Displays the results of the test.
 * The overall score is shown as a fraction and percentage.
 * Each question can be viewed along with the given and true answer.
 */
void results(
	Display& display,
	const Sprite& background,
	const Button& back_button,
	const SignedRenderer& renderer,
	const std::vector<std::unique_ptr<Question>>& questions,
	const std::array<std::unique_ptr<Sprite>, QUESTION_TYPES + 1>& operators,
	int set_count
) {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The user's total score in the test is calculated.
	int score = 0;
	
	for (int i = 0; i < QUESTION_TYPES * set_count; i++) {
		score += questions[i]->correct();
	}
	
	// The current results page.
	int page = 0;
	
	// The sprite that says "Results:"
	Sprite results_sprite(
		RESULTS_SOURCE,
		RESULTS_WIDTH * display_width,
		RESULTS_HEIGHT * display_height
	);
	
	// The '/' sprite.
	Sprite slash_sprite(
		SLASH_SOURCE,
		SLASH_WIDTH * display_width,
		SLASH_HEIGHT * display_height
	);
	
	// The '%' sprite.
	Sprite percent_sprite(
		PERCENT_SOURCE,
		PERCENT_WIDTH * display_width,
		PERCENT_HEIGHT * display_height
	);
	
	// The button that goes to the previous page.
	Button left_button(
		std::make_unique<Sprite>(
			LEFT_SOURCE,
			LEFT_WIDTH * display_width,
			LEFT_HEIGHT * display_height
		),
		display_sprite,
		LEFT_X,
		LEFT_Y
	);
	
	// The button that goes to the next page.
	Button right_button(
		std::make_unique<Sprite>(
			RIGHT_SOURCE,
			RIGHT_WIDTH * display_width,
			RIGHT_HEIGHT * display_height
		),
		display_sprite,
		RIGHT_X,
		RIGHT_Y
	);
	
	// The sprites for the outcomes are loaded.
	std::array<std::unique_ptr<Sprite>, OUTCOME_TYPES> outcomes;
	
	for (int i = 0; i < OUTCOME_TYPES; i++) {
		outcomes[i] = std::make_unique<Sprite>(
			OUTCOME_SOURCES[i],
			QUESTION_WIDTH[2] * QUESTION_WIDTH[0] * display_width,
			QUESTION_HEIGHT * display_height
		);
	}
	
	
	// True when the results should no longer be displayed.
	bool end = false;
	
	// The display is filled with the test's information with each loop.
	while (!end) {
		// The display is blitted to.
		display_sprite.blit(background, 0, 0);
		display_sprite.blit(results_sprite, RESULTS_X, RESULTS_Y);
		display_sprite.blit(slash_sprite, SLASH_X, SLASH_Y);
		display_sprite.blit(percent_sprite, PERCENT_X, PERCENT_Y);
		back_button.blit_to(display_sprite);
		
		// The arrows are only displayed if they can be used.
		if (page) {
			left_button.blit_to(display_sprite);
		}
		
		if (page < set_count - 1) {
			right_button.blit_to(display_sprite);
		}
		
		// The score is blitted to the display.
		display_sprite.blit(
			renderer.render(
				unsigned_string(score, get_digits(score)),
				SCORE_WIDTH * display_width,
				SCORE_HEIGHT * display_height
			),
			SCORE_X,
			SCORE_Y
		);
		
		// The total number of questions are blitted to the display.
		display_sprite.blit(
			renderer.render(
				unsigned_string(
					2 * QUESTION_TYPES * set_count,
					get_digits(2 * QUESTION_TYPES * set_count)
				),
				TOTAL_WIDTH * display_width,
				TOTAL_HEIGHT * display_height
			),
			TOTAL_X,
			TOTAL_Y
		);
		
		// The percentage of questions answered correctly.
		display_sprite.blit(
			renderer.render(
				unsigned_string(
					50 * score / (QUESTION_TYPES * set_count),
					get_digits(50 * score / (QUESTION_TYPES * set_count))
				),
				PERCENTAGE_WIDTH * display_width,
				PERCENTAGE_HEIGHT * display_height
			),
			PERCENTAGE_X,
			PERCENTAGE_Y
		);
		
		// The question set in the page is displayed.
		for (int i = 0; i < QUESTION_TYPES; i++) {
			display_sprite.blit(
				questions[QUESTION_TYPES * page + i]->get_sprite(
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
	}
}

/**
 * Runs the test using the given settings.
 */
void test(
	Display& display,
	const Sprite& background,
	const Button& back_button,
	const SignedRenderer& renderer,
	const std::array<int, 2>& sum_range,
	const std::array<int, 2>& product_range,
	int set_count,
	int time_limit
) {
	// The components of the display are extracted.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The RNG and distributions are initialised.
	std::mt19937 generator(Timer::current());
	std::uniform_int_distribution<int> sum_distribution(
		sum_range[0] < sum_range[1] ? sum_range[0] : sum_range[1],
		sum_range[0] > sum_range[1] ? sum_range[0] : sum_range[1]
	);
	std::uniform_int_distribution<int> product_distribution(
		product_range[0] < product_range[1] ? product_range[0] : product_range[1],
		product_range[0] > product_range[1] ? product_range[0] : product_range[1]
	);
	
	// The sprites for the operators are loaded.
	std::array<std::unique_ptr<Sprite>, QUESTION_TYPES + 1> operators;
	
	for (int i = 0; i <= QUESTION_TYPES; i++) {
		operators[i] = std::make_unique<Sprite>(
			OPERATOR_SOURCES[i],
			OPERATOR_WIDTH * display_width,
			OPERATOR_HEIGHT * display_height
		);
	}
	
	// True if the questions were completed.
	bool finished = true;
	
	// The vector of questions is initialised and the questions are asked.
	std::vector<std::unique_ptr<Question>> questions;
	
	for (int i = 0; i < QUESTION_TYPES * set_count; i++) {
		questions.push_back(std::make_unique<Question>(
			generator,
			sum_distribution,
			product_distribution,
			i % QUESTION_TYPES
		));
		
		if (questions[i]->question(
			display,
			background,
			back_button,
			renderer,
			operators,
			time_limit
		)) {
			finished = false;
			break;
		}
	}
	
	if (finished) {
		results(
			display,
			background,
			back_button,
			renderer,
			questions,
			operators,
			set_count
		);
	}
}

/**
 * Returns values to their bounds if they go beyond them.
 */
void fix_values(
	std::array<int, 2>& sum_range,
	std::array<int, 2>& product_range,
	int& set_count,
	int& time_limit
) {
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
 * Configures the Maths testing for number ranges,
 *   test length, and time to answer per question.
 */
void configure(Display& display, const Sprite& background) {
	// The test is configured to the default settings.
	std::array<int, 2> sum_range = {SUM_MIN, SUM_MAX};
	std::array<int, 2> product_range = {PRODUCT_MIN, PRODUCT_MAX};
	int set_count = SET_COUNT;
	int time_limit = TIME_LIMIT;
	
	// The display's components are stored.
	Sprite& display_sprite = display.get_sprite();
	int display_width = display_sprite.get_width();
	int display_height = display_sprite.get_height();
	
	// The sprite asking for the sum range.
	Sprite sum_sprite(
		SUM_SOURCE,
		SUM_WIDTH * display_width,
		SUM_HEIGHT * display_height
	);
	
	// The sprite asking for the product range.
	Sprite product_sprite(
		PRODUCT_SOURCE,
		PRODUCT_WIDTH * display_width,
		PRODUCT_HEIGHT * display_height
	);
	
	// The sprite asking for the number of question sets.
	Sprite set_sprite(
		SET_SOURCE,
		SET_WIDTH * display_width,
		SET_HEIGHT * display_height
	);
	
	// The sprite asking for the time limit per question.
	Sprite time_sprite(
		TIME_SOURCE,
		TIME_WIDTH * display_width,
		TIME_HEIGHT * display_height
	);
	
	// The sprite that says "to" (for ranges).
	Sprite to_sprite(
		TO_SOURCE,
		TO_WIDTH * display_width,
		TO_HEIGHT * display_height
	);
	
	// The button that returns the user to the main menu.
	Button back_button(
		std::make_unique<Sprite>(
			BACK_SOURCE,
			BACK_WIDTH * display_width,
			BACK_HEIGHT * display_height
		),
		display_sprite,
		BACK_X,
		BACK_Y
	);
	
	// The button that begins the test.
	Button begin_button(
		std::make_unique<Sprite>(
			BEGIN_SOURCE,
			BEGIN_WIDTH * display_width,
			BEGIN_HEIGHT * display_height
		),
		display_sprite,
		BEGIN_X,
		BEGIN_Y
	);
	
	// The sprite that allows a user to increment an option.
	Sprite up_arrow(
		UP_SOURCE,
		UP_WIDTH * display_width,
		UP_HEIGHT * display_height
	);
	
	// The sprite that allows a user to decrement an option.
	Sprite down_arrow(
		DOWN_SOURCE,
		DOWN_WIDTH * display_width,
		DOWN_HEIGHT * display_height
	);
	
	// Produces sprites that represent signed integers.
	SignedRenderer renderer(
		{
			NUMBER_SOURCES[0],
			NUMBER_SOURCES[1],
			NUMBER_SOURCES[2],
			NUMBER_SOURCES[3],
			NUMBER_SOURCES[4],
			NUMBER_SOURCES[5],
			NUMBER_SOURCES[6],
			NUMBER_SOURCES[7],
			NUMBER_SOURCES[8],
			NUMBER_SOURCES[9]
		},
		MINUS_SOURCE
	);
	
	// The rectangles for the up and down arrows are initialised.
	//   Sum rectangles
	std::array<Rectangle, SUM_DIGITS + 1> sum_min_up_rectangles;
	std::array<Rectangle, SUM_DIGITS + 1> sum_min_down_rectangles;
	std::array<Rectangle, SUM_DIGITS + 1> sum_max_up_rectangles;
	std::array<Rectangle, SUM_DIGITS + 1> sum_max_down_rectangles;
	
	//   Rectangle positions and dimensions set.
	for (int i = 0; i <= SUM_DIGITS; i++) {
		sum_min_up_rectangles[i].set_width(UP_WIDTH * display_width);
		sum_min_up_rectangles[i].set_height(UP_HEIGHT * display_height);
		sum_min_up_rectangles[i].set(display_width, display_height, SUM_MIN_X, SUM_MIN_Y);
		sum_min_up_rectangles[i].set_x(
			sum_min_up_rectangles[i].get_x()
			- SUM_DIGITS * sum_min_up_rectangles[i].get_width() / 2
			+ i * sum_min_up_rectangles[i].get_width()
		);
		sum_min_up_rectangles[i].set_y(
			sum_min_up_rectangles[i].get_y()
			- (
				SUM_MIN_HEIGHT * display_height
				+ sum_min_up_rectangles[i].get_height()
			) / 2
		);
		
		sum_min_down_rectangles[i].set_width(DOWN_WIDTH * display_width);
		sum_min_down_rectangles[i].set_height(DOWN_HEIGHT * display_height);
		sum_min_down_rectangles[i].set(display_width, display_height, SUM_MIN_X, SUM_MIN_Y);
		sum_min_down_rectangles[i].set_x(sum_min_up_rectangles[i].get_x());
		sum_min_down_rectangles[i].set_y(
			sum_min_down_rectangles[i].get_y()
			+ (
				SUM_MIN_HEIGHT * display_height
				+ sum_min_down_rectangles[i].get_height()
			) / 2
		);
		
		sum_max_up_rectangles[i].set_width(UP_WIDTH * display_width);
		sum_max_up_rectangles[i].set_height(UP_HEIGHT * display_height);
		sum_max_up_rectangles[i].set(display_width, display_height, SUM_MAX_X, SUM_MAX_Y);
		sum_max_up_rectangles[i].set_x(
			sum_max_up_rectangles[i].get_x()
			- SUM_DIGITS * sum_max_up_rectangles[i].get_width() / 2
			+ i * sum_max_up_rectangles[i].get_width()
		);
		sum_max_up_rectangles[i].set_y(sum_min_up_rectangles[i].get_y());
		
		sum_max_down_rectangles[i].set_width(DOWN_WIDTH * display_width);
		sum_max_down_rectangles[i].set_height(DOWN_HEIGHT * display_height);
		sum_max_down_rectangles[i].set_x(sum_max_up_rectangles[i].get_x());
		sum_max_down_rectangles[i].set_y(sum_min_down_rectangles[i].get_y());
	}
	
	//   Product rectangles
	std::array<Rectangle, PRODUCT_DIGITS + 1> product_min_up_rectangles;
	std::array<Rectangle, PRODUCT_DIGITS + 1> product_min_down_rectangles;
	std::array<Rectangle, PRODUCT_DIGITS + 1> product_max_up_rectangles;
	std::array<Rectangle, PRODUCT_DIGITS + 1> product_max_down_rectangles;
	
	//   Rectangle position and dimensions set
	for (int i = 0; i <= PRODUCT_DIGITS; i++) {
		product_min_up_rectangles[i].set_width(UP_WIDTH * display_width);
		product_min_up_rectangles[i].set_height(UP_HEIGHT * display_height);
		product_min_up_rectangles[i].set(display_width, display_height, PRODUCT_MIN_X, PRODUCT_MIN_Y);
		product_min_up_rectangles[i].set_x(
			product_min_up_rectangles[i].get_x()
			- PRODUCT_DIGITS * product_min_up_rectangles[i].get_width() / 2
			+ i * product_min_up_rectangles[i].get_width()
		);
		product_min_up_rectangles[i].set_y(
			product_min_up_rectangles[i].get_y()
			- (
				PRODUCT_MIN_HEIGHT * display_height
				+ product_min_up_rectangles[i].get_height()
			) / 2
		);
		
		product_min_down_rectangles[i].set_width(DOWN_WIDTH * display_width);
		product_min_down_rectangles[i].set_height(DOWN_HEIGHT * display_height);
		product_min_down_rectangles[i].set(display_width, display_height, PRODUCT_MIN_X, PRODUCT_MIN_Y);
		product_min_down_rectangles[i].set_x(product_min_up_rectangles[i].get_x());
		product_min_down_rectangles[i].set_y(
			product_min_down_rectangles[i].get_y()
			+ (
				PRODUCT_MIN_HEIGHT * display_height
				+ product_min_down_rectangles[i].get_height()
			) / 2
		);
		
		product_max_up_rectangles[i].set_width(UP_WIDTH * display_width);
		product_max_up_rectangles[i].set_height(UP_HEIGHT * display_height);
		product_max_up_rectangles[i].set(display_width, display_height, PRODUCT_MAX_X, PRODUCT_MAX_Y);
		product_max_up_rectangles[i].set_x(
			product_max_up_rectangles[i].get_x()
			- PRODUCT_DIGITS * product_max_up_rectangles[i].get_width() / 2
			+ i * product_max_up_rectangles[i].get_width()
		);
		product_max_up_rectangles[i].set_y(product_min_up_rectangles[i].get_y());
		
		product_max_down_rectangles[i].set_width(DOWN_WIDTH * display_width);
		product_max_down_rectangles[i].set_height(DOWN_HEIGHT * display_height);
		product_max_down_rectangles[i].set_x(product_max_up_rectangles[i].get_x());
		product_max_down_rectangles[i].set_y(product_min_down_rectangles[i].get_y());
	}
	
	//   Question set count rectangles
	std::array<Rectangle, SET_DIGITS> set_count_up_rectangles;
	std::array<Rectangle, SET_DIGITS> set_count_down_rectangles;
	
	//   Rectangle position and dimensions set
	for (int i = 0; i < SET_DIGITS; i++) {
		set_count_up_rectangles[i].set_width(UP_WIDTH * display_width);
		set_count_up_rectangles[i].set_height(UP_HEIGHT * display_height);
		set_count_up_rectangles[i].set(display_width, display_height, SET_COUNT_X, SET_COUNT_Y);
		set_count_up_rectangles[i].set_x(
			set_count_up_rectangles[i].get_x()
			- (SET_DIGITS - 1) * set_count_up_rectangles[i].get_width() / 2
			+ i * set_count_up_rectangles[i].get_width()
		);
		set_count_up_rectangles[i].set_y(
			set_count_up_rectangles[i].get_y()
			- (
				SET_COUNT_HEIGHT * display_height
				+ set_count_up_rectangles[i].get_height()
			) / 2
		);
		
		set_count_down_rectangles[i].set_width(DOWN_WIDTH * display_width);
		set_count_down_rectangles[i].set_height(DOWN_HEIGHT * display_height);
		set_count_down_rectangles[i].set(display_width, display_height, SET_COUNT_X, SET_COUNT_Y);
		set_count_down_rectangles[i].set_x(set_count_up_rectangles[i].get_x());
		set_count_down_rectangles[i].set_y(
			set_count_down_rectangles[i].get_y()
			+ (
				SET_COUNT_HEIGHT * display_height
				+ set_count_down_rectangles[i].get_height()
			) / 2
		);
	}
	
	//   Time limit rectangles
	std::array<Rectangle, TIME_DIGITS> time_limit_up_rectangles;
	std::array<Rectangle, TIME_DIGITS> time_limit_down_rectangles;
	
	//   Rectangle position and dimensions set
	for (int i = 0; i < TIME_DIGITS; i++) {
		time_limit_up_rectangles[i].set_width(UP_WIDTH * display_width);
		time_limit_up_rectangles[i].set_height(UP_HEIGHT * display_height);
		time_limit_up_rectangles[i].set(display_width, display_height, TIME_LIMIT_X, TIME_LIMIT_Y);
		time_limit_up_rectangles[i].set_x(
			time_limit_up_rectangles[i].get_x()
			- (TIME_DIGITS - 1) * time_limit_up_rectangles[i].get_width() / 2
			+ i * time_limit_up_rectangles[i].get_width()
		);
		time_limit_up_rectangles[i].set_y(
			time_limit_up_rectangles[i].get_y()
			- (
				TIME_LIMIT_HEIGHT * display_height
				+ time_limit_up_rectangles[i].get_height()
			) / 2
		);
		
		time_limit_down_rectangles[i].set_width(DOWN_WIDTH * display_width);
		time_limit_down_rectangles[i].set_height(DOWN_HEIGHT * display_height);
		time_limit_down_rectangles[i].set(display_width, display_height, TIME_LIMIT_X, TIME_LIMIT_Y);
		time_limit_down_rectangles[i].set_x(time_limit_up_rectangles[i].get_x());
		time_limit_down_rectangles[i].set_y(
			time_limit_down_rectangles[i].get_y()
			+ (
				TIME_LIMIT_HEIGHT * display_height
				+ time_limit_down_rectangles[i].get_height()
			) / 2
		);
	}
	
	// Set to true, when the main menu should be returned to.
	bool back = false;
	
	// Loop for the configuration menu.
	// The configuration menu is displayed with each loop.
	while (!back) {
		// Values that were moved out of range are moved back in range.
		fix_values(sum_range, product_range, set_count, time_limit);
		
		// The display is blitted to and updated.
		//   Basic sprites are blitted.
		display_sprite.blit(background, 0, 0);
		display_sprite.blit(sum_sprite, SUM_X, SUM_Y);
		display_sprite.blit(product_sprite, PRODUCT_X, PRODUCT_Y);
		display_sprite.blit(set_sprite, SET_X, SET_Y);
		display_sprite.blit(time_sprite, TIME_X, TIME_Y);
		display_sprite.blit(to_sprite, TO_X[0], TO_Y[0]);
		display_sprite.blit(to_sprite, TO_X[1], TO_Y[1]);
		
		//   Rendered numbers are blitted.
		display_sprite.blit(
			renderer.render(
				signed_string(sum_range[0], SUM_DIGITS),
				SUM_MIN_WIDTH * display_width,
				SUM_MIN_HEIGHT * display_height
			),
			SUM_MIN_X,
			SUM_MIN_Y
		);
		display_sprite.blit(
			renderer.render(
				signed_string(sum_range[1], SUM_DIGITS),
				SUM_MAX_WIDTH * display_width,
				SUM_MAX_HEIGHT * display_height
			),
			SUM_MAX_X,
			SUM_MAX_Y
		);
		display_sprite.blit(
			renderer.render(
				signed_string(product_range[0], PRODUCT_DIGITS),
				PRODUCT_MIN_WIDTH * display_width,
				PRODUCT_MIN_HEIGHT * display_height
			),
			PRODUCT_MIN_X,
			PRODUCT_MIN_Y
		);
		display_sprite.blit(
			renderer.render(
				signed_string(product_range[1], PRODUCT_DIGITS),
				PRODUCT_MAX_WIDTH * display_width,
				PRODUCT_MAX_HEIGHT * display_height
			),
			PRODUCT_MAX_X,
			PRODUCT_MAX_Y
		);
		display_sprite.blit(
			renderer.render(
				unsigned_string(set_count, SET_DIGITS),
				SET_COUNT_WIDTH * display_width,
				SET_COUNT_HEIGHT * display_height
			),
			SET_COUNT_X,
			SET_COUNT_Y
		);
		display_sprite.blit(
			renderer.render(
				unsigned_string(time_limit, TIME_DIGITS),
				TIME_LIMIT_WIDTH * display_width,
				TIME_LIMIT_HEIGHT * display_height
			),
			TIME_LIMIT_X,
			TIME_LIMIT_Y
		);
		
		//   Arrow pseudo-buttons are blitted.
		for (int i = 0; i <= SUM_DIGITS; i++) {
			display_sprite.blit(up_arrow, sum_min_up_rectangles[i]);
			display_sprite.blit(down_arrow, sum_min_down_rectangles[i]);
			display_sprite.blit(up_arrow, sum_max_up_rectangles[i]);
			display_sprite.blit(down_arrow, sum_max_down_rectangles[i]);
		}
		
		for (int i = 0; i <= PRODUCT_DIGITS; i++) {
			display_sprite.blit(up_arrow, product_min_up_rectangles[i]);
			display_sprite.blit(down_arrow, product_min_down_rectangles[i]);
			display_sprite.blit(up_arrow, product_max_up_rectangles[i]);
			display_sprite.blit(down_arrow, product_max_down_rectangles[i]);
		}
		
		for (int i = 0; i < SET_DIGITS; i++) {
			display_sprite.blit(up_arrow, set_count_up_rectangles[i]);
			display_sprite.blit(down_arrow, set_count_down_rectangles[i]);
		}
		
		for (int i = 0; i < TIME_DIGITS; i++) {
			display_sprite.blit(up_arrow, time_limit_up_rectangles[i]);
			display_sprite.blit(down_arrow, time_limit_down_rectangles[i]);
		}
		
		//   Control buttons are blitted.
		back_button.blit_to(display_sprite);
		begin_button.blit_to(display_sprite);
		
		//   The display is updated.
		display.update();
		
		// Loop for user input.
		while (true) {
			// Stores the mouse's position.
			Point mouse;
			
			// If the quit key is pressed and released, the main menu is returned to.
			if (Events::unpress(QUIT_KEY)) {
				back = true;
				break;
			}
			
			// Else, if the submit key was pressed, the test begins.
			else if (Events::unpress(SUBMIT_KEY)) {
				test(
					display,
					background,
					back_button,
					renderer,
					sum_range,
					product_range,
					set_count,
					time_limit
				);
				break;
			}
			
			// If the user clicked and released, the position of the mouse is checked.
			else if (Events::unclick(Events::LEFT_CLICK, mouse)) {
				// If the back button was clicked, the main menu is returned to.
				if (back_button.get_rectangle().contains(mouse)) {
					back = true;
					break;
				}
				
				// Else, if the begin button was clicked, the test begins.
				else if (begin_button.get_rectangle().contains(mouse)) {
					test(
						display,
						background,
						back_button,
						renderer,
						sum_range,
						product_range,
						set_count,
						time_limit
					);
					break;
				}

				// The first pair of arrows, for sum and product ranges, changes the sign.
				//   Minimum sum value sign switch.
				else if (
					sum_min_up_rectangles[0].contains(mouse)
					|| sum_min_down_rectangles[0].contains(mouse)
				) {
					sum_range[0] *= -1;
					break;
				}
				
				//   Maximum sum value sign switch.
				else if (
					sum_max_up_rectangles[0].contains(mouse)
					|| sum_max_down_rectangles[0].contains(mouse)
				) {
					sum_range[1] *= -1;
					break;
				}
				
				//   Minimum product value sign switch.
				else if (
					product_min_up_rectangles[0].contains(mouse)
					|| product_min_down_rectangles[0].contains(mouse)
				) {
					product_range[0] *= -1;
					break;
				}
				
				//   Maximum product value sign switch.
				else if (
					product_max_up_rectangles[0].contains(mouse)
					|| product_max_down_rectangles[0].contains(mouse)
				) {
					product_range[1] *= -1;
					break;
				}
				
				// The arrows change the values.
				else {
					bool done = false;
					
					//   Sum range value modifiers.
					for (int i = SUM_DIGITS, change = 1; !done && i > 0; i--, change *= 10) {
						if (sum_min_up_rectangles[i].contains(mouse)) {
							sum_range[0] += change;
							done = true;
						}
						
						else if (sum_min_down_rectangles[i].contains(mouse)) {
							sum_range[0] -= change;
							done = true;
						}
						
						else if (sum_max_up_rectangles[i].contains(mouse)) {
							sum_range[1] += change;
							done = true;
						}
						
						else if (sum_max_down_rectangles[i].contains(mouse)) {
							sum_range[1] -= change;
							done = true;
						}
					}
					
					//   Product range value modifiers.
					for (int i = PRODUCT_DIGITS, change = 1; !done && i > 0; i--, change *= 10) {
						if (product_min_up_rectangles[i].contains(mouse)) {
							product_range[0] += change;
							done = true;
						}
						
						else if (product_min_down_rectangles[i].contains(mouse)) {
							product_range[0] -= change;
							done = true;
						}
						
						else if (product_max_up_rectangles[i].contains(mouse)) {
							product_range[1] += change;
							done = true;
						}
						
						else if (product_max_down_rectangles[i].contains(mouse)) {
							product_range[1] -= change;
							done = true;
						}
					}
					
					//   Question set count value modifiers.
					for (int i = SET_DIGITS - 1, change = 1; !done && i >= 0; i--, change *= 10) {
						if (set_count_up_rectangles[i].contains(mouse)) {
							set_count += change;
							done = true;
						}
						
						else if (set_count_down_rectangles[i].contains(mouse)) {
							set_count -= change;
							done = true;
						}
					}
					
					//   Time per question value modifiers.
					for (int i = TIME_DIGITS - 1, change = 1; !done && i >= 0; i--, change *= 10) {
						if (time_limit_up_rectangles[i].contains(mouse)) {
							time_limit += change;
							done = true;
						}
						
						else if (time_limit_down_rectangles[i].contains(mouse)) {
							time_limit -= change;
							done = true;
						}
					}
					
					// If a button was clicked, the display should be rendered again.
					if (done) {
						break;
					}
				}
			}
			
			Events::update();
		}
	}
}

/**
 * An automatic mental maths quizzer with customisable difficulty and length.
 */
int main(int arcg, char** argv) {
	System::initialise(System::VIDEO | System::AUDIO, false);
	
	std::cout
		<< "\nAutoSchool: Mathematics by Chigozie Agomo.\nVersion: "
		<< System::version(VERSION, VERSION_LENGTH) << '\n'
		<< System::info()
	;
	
	// Scope to ensure that the objects are destroyed before SDL is terminated.
	{
		// The display system is initialised (windowed fullscreen).
		Display display(0, 0);
		Sprite& display_sprite = display.get_sprite();
		int display_width = display_sprite.get_width();
		int display_height = display_sprite.get_height();
		
		// The background sprite.
		Sprite background(
			BACKGROUND_SOURCE,
			display_width,
			display_height
		);
		
		// The title sprite.
		Sprite title(
			TITLE_SOURCE,
			TITLE_WIDTH * display_width,
			TITLE_HEIGHT * display_height
		);
		
		// The copyright and support button.
		Button copyright(
			std::make_unique<Sprite>(
				COPYRIGHT_SOURCE,
				COPYRIGHT_WIDTH * display_width,
				COPYRIGHT_HEIGHT * display_height
			),
			display_sprite,
			COPYRIGHT_X,
			COPYRIGHT_Y
		);
		
		// The start button.
		Button start(
			std::make_unique<Sprite>(
				START_SOURCE,
				START_WIDTH * display_width,
				START_HEIGHT * display_height
			),
			display_sprite,
			START_X,
			START_Y
		);
		
		// The info button.
		Button info(
			std::make_unique<Sprite>(
				INFO_SOURCE,
				INFO_WIDTH * display_width,
				INFO_HEIGHT * display_height
			),
			display_sprite,
			INFO_X,
			INFO_Y
		);
		
		// The quit button.
		Button quit(
			std::make_unique<Sprite>(
				QUIT_SOURCE,
				QUIT_WIDTH * display_width,
				QUIT_HEIGHT * display_height
			),
			display_sprite,
			QUIT_X,
			QUIT_Y
		);
		
		// The music is loaded and queued in another thread until the program ends.
		Audio audio(MUSIC_SOURCE, MUSIC_LENGTH);
		Thread thread(queue_audio, &audio);
		
		// Set to true when the program should end.
		bool end = false;
		
		// Loop for the main menu.
		// The main menu is displayed each loop.
		while (!end) {
			display_sprite.blit(background, 0, 0);
			display_sprite.blit(title, TITLE_X, TITLE_Y);
			copyright.blit_to(display_sprite);
			start.blit_to(display_sprite);
			info.blit_to(display_sprite);
			quit.blit_to(display_sprite);
			display.update();
			
			// Input is waited for.
			while (true) {
				Point mouse;
				
				// If the quit button is pressed, the program terminates.
				if (Events::press(QUIT_KEY)) {
					end = true;
					break;
				}
				
				// Else, if the start button was clicked,
				//   the configurator screen is moved to.
				else if (Events::unpress(SUBMIT_KEY)) {
					configure(display, background);
					break;
				}
					
				// Else, if the mouse was clicked, its position is stored upon release.
				else if (Events::unclick(Events::LEFT_CLICK, mouse)) {
					// If the quit button was clicked, the program terminates.
					if (quit.get_rectangle().contains(mouse)) {
						end = true;
						break;
					}
					
					// Else, if the copyright button was clicked, the
					//   support link is opened in the default browser.
					else if (copyright.get_rectangle().contains(mouse)) {
						support();
					}
					
					// Else, if the info button was clicked,
					//   the program's info is displayed.
					else if (info.get_rectangle().contains(mouse)) {
						display_info(display);
						break;
					}
					
					// Else, if the start button was clicked,
					//   the configurator screen is moved to.
					else if (start.get_rectangle().contains(mouse)) {
						configure(display, background);
						break;
					}
				}
				
				Events::update();
			}
		}
		
		// Pauses the audio to signify that the queue_audio should terminate.
		audio.pause();
		thread.wait();
	}
	
	System::terminate();
	
	return 0;
}

/* CHANGELOG:
     v1.0.1:
	   Added keybindings for the results page.
	 v1.0.2:
	   Renamed v1.1 to v1.0.1
	   Enter can now advance the page in the menus.
	   Added a version message that is printed to standard output
	     at the start of the program.
	 v1.0.2.1:
	   Now uses sdlandnet.hpp v1.0.0.1 (instead of v0.8.5).
	 v1.0.3:
	   Results arrows are no longer displayed if they take no effect.
	   The .dll files were updated.
	 v-1.0.3:
	   Changes to accomodate mobile devices (onscreen buttons).
	 v-1.0.4:
	   Rearranged the position of the question and the buttons.
	   The results display now reloads the operator sprites.
 */

// Note that std::to_string() was not used, due to MinGW being bugged.