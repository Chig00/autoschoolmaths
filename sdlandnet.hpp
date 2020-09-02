#include <string>
#include <sstream>
#include <memory>
#include <array>
#include <cmath>
#include <ctime>
#include <SDL.h>
#include <SDL_net.h>

constexpr int LETTERS = 26;
constexpr int NUMBERS = 10;

constexpr int SDL_AND_NET_VERSION[] = {1, 0, 0, 2};
constexpr int SDL_AND_NET_VERSION_LENGTH = 4;

/**
 * A namespace for initialisation and shutdown functions.
 */
namespace System {
	// For use with the initialise() function
	constexpr int VIDEO = SDL_INIT_VIDEO;
	constexpr int AUDIO = SDL_INIT_AUDIO;
	
	/**
	 * Returns the version in string form.
	 */
	std::string version(
		const int* version = SDL_AND_NET_VERSION,
		int version_length = SDL_AND_NET_VERSION_LENGTH
	) noexcept {
		std::stringstream stream;
		
		for (int i = 0; i < version_length; i++) {
			stream << version[i];
			
			if (i < version_length - 1) {
				stream << '.';
			}
		}
		
		return stream.str();
	}
	
	/**
	 * Returns a string of information about this library.
	 */
	std::string info() noexcept {
		std::stringstream stream;
		stream
			<< "\nSDL and SDL Net utilities by Chigozie Agomo.\nVersion: "
			<< version() << '\n'
		;
		
		return stream.str();
	}
	
	/**
	 * Initialises SDL with the given flags.
	 * Optionally intialises SDL_net.
	 */
	void initialise(int flags = VIDEO, bool init_net = false) noexcept {
		SDL_Init(flags);
		
		if (init_net) {
			SDLNet_Init();
		}
	}

	/**
	 * Shutdowns SDL_net and SDL.
	 */
	void terminate() noexcept {
		SDLNet_Quit();
		SDL_Quit();
	}

	/**
	 * Sends the given command to the command line.
	 */
	void command(const std::string& command_string) noexcept {
		system(command_string.c_str());
	}
}

/**
 * A namespace for time related functions.
 */
namespace Timer {
	/**
	 * Returns the time in seconds elapsed since the epoch.
	 */
	int current() noexcept {
		return time(NULL);
	}
	
	/**
	 * Returns the time in seconds.
	 * All times returned are relative to each other.
	 */
	double time() noexcept {
		return static_cast<double>(clock()) / CLOCKS_PER_SEC;
	}

	/**
	 * Halts all functionality in the thread for the
	 *   specified amount of time (in seconds).
	 */
	void wait(double seconds) noexcept {
		double now = time();
		while (time() < now + seconds);
	}
}

/**
 * A wrapper class for SDL_Points.
 * Manages a pair of coordinates and its functionality.
 */
class Point {
	public:
		/**
		 * Constructs a new Point instance at the given position.
		 */
		Point(int x = 0, int y = 0) noexcept {
			set(x, y);
		}
		
		/**
		 * Constructs a new Point instance with the given SDL_Point.
		 */
		Point(SDL_Point p) noexcept {
			point = p;
		}
		
		/**
		 * Returns true if the coordinates of the given Point
		 *   matches the points of this point.
		 */
		bool operator==(const Point& p) const noexcept {
			return point.x == p.point.x && point.y == p.point.y;
		}
		
		/**
		 * Returns true if the coordinates of the given
		 *   SDL_Point matches the points of this point.
		 */
		bool operator==(SDL_Point p) const noexcept {
			return point.x == p.x && point.y == p.y;
		}
		
		/**
		 * Sets the point with the given SDL_Point.
		 */
		Point& operator=(SDL_Point p) noexcept {
			point = p;
			
			return *this;
		}
		
		/**
		 * Sets the point to be at the given position.
		 */
		void set(int x = 0, int y = 0) noexcept {
			point.x = x;
			point.y = y;
		}
		
		/**
		 * Sets the x coordinate.
		 */
		void set_x(int x = 0) noexcept {
			point.x = x;
		}
		
		/**
		 * Sets the y coordinate.
		 */
		void set_y(int y = 0) noexcept {
			point.y = y;
		}
		
		/**
		 * Returns a pointer to the internal SDL_Point.
		 */
		const SDL_Point* get() const noexcept {
			return &point;
		}
		
		/**
		 * Returns the x coordinate.
		 */
		int get_x() const noexcept {
			return point.x;
		}
		
		/**
		 * Returns the y coordinate.
		 */
		int get_y() const noexcept {
			return point.y;
		}
		
		/**
		 * Returns the distance between the given point and this one.
		 */
		double get_distance(const Point& p) const noexcept {
			return get_distance(p.point.x, p.point.y);
		}
		
		/**
		 * Returns the distnace between the given
		 *   coordinates and this one.
		 */
		double get_distance(int x = 0, int y = 0) const noexcept {
			return sqrt(
				pow(point.x - x, 2)
				+ pow(point.y - y, 2)
			);
		}
		
	private:	
		SDL_Point point; // The internal point
};

/**
 * A namespace for event handling functions.
 */
namespace Events {
	// For use with mouse click functions.
	constexpr int LEFT_CLICK = SDL_BUTTON(SDL_BUTTON_LEFT);
	constexpr int MIDDLE_CLICK = SDL_BUTTON(SDL_BUTTON_MIDDLE);
	constexpr int RIGHT_CLICK = SDL_BUTTON(SDL_BUTTON_RIGHT);
	
	constexpr int LETTERS[] = {
		SDL_SCANCODE_A,
		SDL_SCANCODE_B,
		SDL_SCANCODE_C,
		SDL_SCANCODE_D,
		SDL_SCANCODE_E,
		SDL_SCANCODE_F,
		SDL_SCANCODE_G,
		SDL_SCANCODE_H,
		SDL_SCANCODE_I,
		SDL_SCANCODE_J,
		SDL_SCANCODE_K,
		SDL_SCANCODE_L,
		SDL_SCANCODE_M,
		SDL_SCANCODE_N,
		SDL_SCANCODE_O,
		SDL_SCANCODE_P,
		SDL_SCANCODE_Q,
		SDL_SCANCODE_R,
		SDL_SCANCODE_S,
		SDL_SCANCODE_T,
		SDL_SCANCODE_U,
		SDL_SCANCODE_V,
		SDL_SCANCODE_W,
		SDL_SCANCODE_X,
		SDL_SCANCODE_Y,
		SDL_SCANCODE_Z
	};
	
	constexpr int NUMBERS[] = {
		SDL_SCANCODE_0,
		SDL_SCANCODE_1,
		SDL_SCANCODE_2,
		SDL_SCANCODE_3,
		SDL_SCANCODE_4,
		SDL_SCANCODE_5,
		SDL_SCANCODE_6,
		SDL_SCANCODE_7,
		SDL_SCANCODE_8,
		SDL_SCANCODE_9
	};
	
	constexpr int UP = SDL_SCANCODE_UP;
	constexpr int DOWN = SDL_SCANCODE_DOWN;
	constexpr int LEFT = SDL_SCANCODE_LEFT;
	constexpr int RIGHT = SDL_SCANCODE_RIGHT;
	constexpr int ESCAPE = SDL_SCANCODE_ESCAPE;
	constexpr int SPACE = SDL_SCANCODE_SPACE;
	constexpr int BACKSPACE = SDL_SCANCODE_BACKSPACE;
	constexpr int ENTER = SDL_SCANCODE_RETURN;
	constexpr int LEFT_SHIFT = SDL_SCANCODE_LSHIFT;
	constexpr int RIGHT_SHIFT = SDL_SCANCODE_RSHIFT;
	constexpr int MINUS = SDL_SCANCODE_MINUS;
	constexpr int EQUALS = SDL_SCANCODE_EQUALS;
	
	/**
	 * Updates the events.
	 * Should be called for each event check loop.
	 */
	void update() noexcept {
		SDL_PumpEvents();
	}
	
	/**
	 * Returns true if the given key is being pressed.
	 */
	bool press(int key) noexcept {
		return SDL_GetKeyboardState(nullptr)[key];
	}
	
	/**
	 * Returns true upon the release of the given key.
	 * All functionality of the thread is halted until
	 *   the key is released.
	 */
	bool unpress(int key) noexcept {
		// The key press is assumed to be false.
		bool pressed = false;
		
		// If the key was pressed,
		if (press(key)) {
			// the release is waited for
			while (press(key)) {
				update();
			}
			
			// and pressed is set to true.
			pressed = true;
		}
		
		// The key press status is returned.
		return pressed;
	}

	/**
	 * Returns true if the given mouse button is being clicked.
	 */
	bool click(int button = LEFT_CLICK) noexcept {
		return SDL_GetMouseState(nullptr, nullptr) & button;
	}
	
	/**
	 * Returns true if the given mouse button is being clicked.
	 * Fills in the integers passed with the mouse's coordinates.
	 */
	bool click(int button, int& x, int& y) noexcept {
		return SDL_GetMouseState(&x, &y) & button;
	}
	
	/**
	 * Returns true if the given mouse button is being clicked.
	 * Fills in the Point passed with the mouse's coordinates.
	 */
	bool click(int button, Point& point) noexcept {
		int x;
		int y;
		bool state = click(button, x, y);
		point.set(x, y);
		
		return state;
	}
	
	/**
	 * Returns true upon the release of the given mouse button.
	 * All functionality of the thread is halted until
	 *   the button is released.
	 * Note that this function will only terminate if the mouse
	 *   click is released, which means that subsequent calls
	 *   without calling Events::update() will always return false.
	 * Store the position of the mouse, in order to
	 *   perform multiple mouse position tests.
	 */
	bool unclick(int button = LEFT_CLICK) noexcept {
		// The button click is assumed to be false.
		bool clicked = false;
		
		// If the button was clicked,
		if (click(button)) {
			// the release is waited for
			while (click(button)) {
				update();
			}
			
			// and clicked is set to true.
			clicked = true;
		}
		
		// The button click status is returned.
		return clicked;
	}
	
	/**
	 * Returns true upon the release of the given mouse button.
	 * Fills in the integers passed with the mouse's coordinates.
	 * All functionality of the thread is halted until
	 *   the button is released.
	 * Note that this function will only terminate if the mouse
	 *   click is released, which means that subsequent calls
	 *   without calling Events::update() will always return false.
	 * Store the position of the mouse, in order to
	 *   perform multiple mouse position tests.
	 */
	bool unclick(int button, int& x, int& y) noexcept {
		// The button click is assumed to be false.
		bool clicked = false;
		
		// If the button was clicked,
		if (click(button)) {
			// the release is waited for
			while (click(button, x, y)) {
				update();
			}
			
			// and clicked is set to true.
			clicked = true;
		}
		
		// The button click status is returned.
		return clicked;
	}
	
	/**
	 * Returns true upon the release of the given mouse button.
	 * Fills in the Point passed with the mouse's coordinates.
	 * All functionality of the thread is halted until
	 *   the button is released.
	 * Note that this function will only terminate if the mouse
	 *   click is released, which means that subsequent calls
	 *   without calling Events::update() will always return false.
	 * Store the position of the mouse, in order to
	 *   perform multiple mouse position tests.
	 */
	bool unclick(int button, Point& point) noexcept {
		int x;
		int y;
		bool state = unclick(button, x, y);
		point.set(x, y);
		
		return state;
	}
}

/**
 * An abstract class for the two types of TCP messengers
 *   to inherit from.
 * This class cannot and should not be instantiated.
 */
class Messenger {
	public:
		/**
		 * Sends the string passed to the other messenger.
		 */
		void send(const std::string& message) const noexcept {
			SDLNet_TCP_Send(socket, message.c_str(), message.length() + 1);
		}
		
		/**
		 * Receives a string from the other messenger.
		 * A maximum number of bytes, equal to buffer_size, is read.
		 * Uses C-style strings internally, so buffer_size,
		 *   should be one greater than the length of the string sent.
		 */
		std::string read(int buffer_size) const noexcept {
			char* buffer = new char[buffer_size];
			SDLNet_TCP_Recv(socket, buffer, buffer_size);
			std::string message(buffer);
			delete[] buffer;
			return message;
		}

	protected:
		Messenger() {}    // This is an abstract base class.
		TCPsocket socket; // THe TCP socket used for the connection.
};

/**
 * A Messenger subclass for the server.
 */
class Server: public Messenger {
	public:
		/**
		 * Constructs a new TCP messenger for the server.
		 * The server is hosted at localhost:[port].
		 */
		Server(int port) noexcept {
			IPaddress ip_address;
			SDLNet_ResolveHost(&ip_address, nullptr, port);
			server = SDLNet_TCP_Open(&ip_address);
			while (!(socket = SDLNet_TCP_Accept(server)));
		}
		
		/**
		 * Closes the TCP sockets associated with the messenger.
		 */
		~Server() noexcept {
			SDLNet_TCP_Close(socket);
			SDLNet_TCP_Close(server);
		}
		
	private:
		TCPsocket server; // The TCP socket used for to accept the client.
};

/**
 * A Messenger subclass for the client.
 */
class Client: public Messenger {
	public:
		/**
		 * Constructs a new TCP messenger for the client.
		 * The client connects to the server at [address]:[port].
		 */
		Client(const std::string& address, int port) noexcept {
			IPaddress ip_address;
			SDLNet_ResolveHost(&ip_address, address.c_str(), port);
			socket = SDLNet_TCP_Open(&ip_address);
		}
		
		/**
		 * Closes the TCP socket associated with the messenger.
		 */
		~Client() noexcept {
			SDLNet_TCP_Close(socket);
		}
};

/**
 * An enumeration of various predefined colours.
 * Used with the sprite filling methods.
 */
enum Colour {
	BLACK,   // 000000
	RED,     // ff0000
	GREEN,   // 00ff00
	BLUE,    // 0000ff
	YELLOW,  // ffff00
	CYAN,    // 00ffff
	MAGENTA, // ff00ff
	WHITE    // ffffff
};

/**
 * An abstract base class for shapes to inherit from.
 * All shapes must have the ability to state if they contain
 *   a given Point, which also allowed them to state if they
 *   are being clicked.
 */
class Shape {
	public:
		/**
		 * Returns true if the Point is contained within the shape.
		 */
		virtual bool contains(const Point&) const noexcept = 0;
		
		/**
		 * Returns true if the given mouse button is being clicked and
		 *   the position of the mouse is contained within the shape.
		 */
		bool click(int button = Events::LEFT_CLICK) const noexcept {
			Point point;
			
			return
				Events::click(button, point)
				&& contains(point)
			;
		}
		
		/**
		 * Returns true upon the release of the given mouse
		 *   button in the bounds of the shape.
		 * Halts all functionality of the thread until
		 *   the mouse button is released.
		 * Note that this method will only terminate if the mouse
		 *   click is released, which means that subsequent calls
		 *   without calling Events::update() will always return false.
		 * Use Events::unclick() and store the position of the mouse,
		 *   in order to perform multiple mouse position tests.
		 */
		bool unclick(int button = Events::LEFT_CLICK) const noexcept {
			Point point;
			
			return
				Events::unclick(button, point)
				&& contains(point)
			;
		}
};

/**
 * A wrapper class for the SDL_Rect.
 * Manages a pair of coordinates, a pair of dimensions,
 *   and their functionality.
 */
class Rectangle: public Shape {
	public:
		/**
		 * Constructs a new Rectangle with the given position
		 *   and dimensions.
		 */
		Rectangle(int x = 0, int y = 0, int w = 0, int h = 0) noexcept {
			set(x, y, w, h);
		}
		
		/**
		 * Constructs a new Rectangle with the given SDL_Rect.
		 */
		Rectangle(SDL_Rect r) noexcept {
			rectangle = r;
		}
		
		/**
		 * Returns true if the given Rectangle covers
		 *   the exact same area as this one.
		 */
		bool operator==(const Rectangle& r) const noexcept {
			return SDL_RectEquals(&rectangle, &r.rectangle);
		}
		
		/**
		 * Returns true if the given SDL_Rect covers
		 *   the exact same area as this one.
		 */
		bool operator==(SDL_Rect r) const noexcept {
			return SDL_RectEquals(&rectangle, &r);
		}
		
		/**
		 * Sets this object to cover the exact same area
		 *   as the given SDL_Rect.
		 */
		Rectangle& operator=(SDL_Rect r) noexcept {
			rectangle = r;
			
			return *this;
		}
		
		/**
		 * Sets the position and dimensions of this Rectangle.
		 */
		void set(int x = 0, int y = 0, int w = 0, int h = 0) noexcept {
			rectangle.x = x;
			rectangle.y = y;
			rectangle.w = w;
			rectangle.h = h;
		}
		
		/**
		 * Sets the rectangle's position according to the same rules as
		 *   Sprite::blit(const Surface&, double, double).
		 * The width and height should correspond to the width
		 *   and height of the template sprite.
		 * Uses the given sprite as a template for this.
		 */
		void set(int width, int height, double x = 0.5, double y = 0.5) noexcept {
			rectangle.x = x * width - rectangle.w / 2;
			rectangle.y = y * height - rectangle.h / 2;
		}
		
		/**
		 * Sets the left edge's position of the rectangle.
		 */
		void set_x(int x = 0) noexcept {
			rectangle.x = x;
		}
		
		/**
		 * Sets the top edge's position of the rectangle.
		 */
		void set_y(int y = 0) noexcept {
			rectangle.y = y;
		}
		
		/**
		 * Sets the width of the rectangle.
		 */
		void set_width(int width = 0) noexcept {
			rectangle.w = width;
		}
		
		/**
		 * Sets the height of the rectangle.
		 */
		void set_height(int height = 0) noexcept {
			rectangle.h = height;
		}
		
		/**
		 * Returns a pointer to the internal SDL_Rect.
		 */
		const SDL_Rect* get() const noexcept {
			return &rectangle;
		}
		
		/**
		 * Returns the left edge's position.
		 */
		int get_x() const noexcept {
			return rectangle.x;
		}
		
		/**
		 * Returns the top edge's position.
		 */
		int get_y() const noexcept {
			return rectangle.y;
		}
		
		/**
		 * Returns the rectangle's width.
		 */
		int get_width() const noexcept {
			return rectangle.w;
		}
		
		/**
		 * Returns the rectangle's height.
		 */
		int get_height() const noexcept {
			return rectangle.h;
		}
		
		/**
		 * Constructs and returns a Point at the Rectangle's
		 * top-left vertex.
		 */
		Point get_point() const noexcept {
			return Point(rectangle.x, rectangle.y);
		}
		
		/**
		 * Returns true if the given point is inside
		 *   of this rectangle.
		 */
		bool contains(const Point& point) const noexcept {
			return SDL_PointInRect(point.get(), &rectangle);
		}
		
		/**
		 * Returns true if the given rectangle
		 *   intersects with this one.
		 */
		bool intersects(const Rectangle& r) const noexcept {
			return SDL_HasIntersection(&r.rectangle, &rectangle);
		}
		
	private:
		SDL_Rect rectangle; // The internal rectangle
};

/**
 * A class derived from Shape to represent a circle.
 */
class Circle: public Shape {
	public:
		/**
		 * Constructs a circle at the given coordinates
		 *   and with the given radius.
		 */
		Circle(int x = 0, int y = 0, int r = 0) noexcept: point(x, y) {
			radius = r;
		}
		
		/**
		 * Constructs a circle at the given point
		 *   with the given radius.
		 */
		Circle(const Point& p, int r = 0) noexcept: point(p) {
			radius = r;
		}
		
		/**
		 * Returns true if the given circle covers
		 *   the same area as this one.
		 */
		bool operator==(const Circle& c) const noexcept {
			return point == c.point && radius == c.radius;
		}
		
		/**
		 * Sets the circle's position and radius.
		 */
		void set(int x, int y, int r) noexcept {
			set(x, y);
			radius = r;
		}
		
		/**
		 * Sets the circle's position and radius.
		 */
		void set(const Point& p, int r = 0) noexcept {
			point = p;
			radius = r;
		}
		
		/**
		 * Sets the circle's position.
		 */
		void set(int x, int y) noexcept {
			set_x(x);
			set_y(y);
		}
		
		/**
		 * Sets the circle's position.
		 */
		void set(const Point& p) noexcept {
			point = p;
		}
		
		/**
		 * Sets the circle's x coordinate.
		 */
		void set_x(int x = 0) noexcept {
			point.set_x(x);
		}
		
		/**
		 * Sets the circle's y coordinate.
		 */
		void set_y(int y = 0) noexcept {
			point.set_y(y);
		}
		
		/**
		 * Sets the circle's radius.
		 */
		void set_radius(int r = 0) noexcept {
			radius = r;
		}
		
		/**
		 * Returns a reference to the circle's Point instance.
		 */
		Point& get_point() noexcept {
			return point;
		}
		
		/**
		 * Returns the circle's x coordinate.
		 */
		int get_x() const noexcept {
			return point.get_x();
		}
		
		/**
		 * Returns the circle's y coordinate.
		 */
		int get_y() const noexcept {
			return point.get_y();
		}
		
		/**
		 * Returns the circle's radius.
		 */
		int get_radius() const noexcept {
			return radius;
		}
		
		/**
		 * Returns true if the given Point is contained within the circle.
		 */
		bool contains(const Point& p) const noexcept {
			return point.get_distance(p) <= radius;
		}
		
	private:
		Point point; // The centre of the circle.
		int radius;  // The radius of the circle.
};

/**
 * A wrapper class for SDL_Surfaces.
 * Manages the blitting of one surface to another.
 * Also allows for the surface or a rectangular section
 *   of it to be filled in with a single colour.
 * Instances of this class are not copiable, but are movable.
 */
class Sprite {
	public:
		/**
		 * Constructs a new Sprite object using the given surface.
		 */
		Sprite(SDL_Surface* surf) noexcept {
			surface = surf;
		}
		
		/**
		 * Constructs a new Sprite object.
		 * The Sprite is created with the given dimenions.
		 */
		Sprite(int width = 0, int height = 0) noexcept {
			create_surface(width, height);
		}
		
		/**
		 * Constructs a new Sprite object.
		 * The Sprite is created with the given dimenions.
		 * The Sprite is filled in with the given colour.
		 */
		Sprite(int width, int height, int red, int green, int blue) noexcept {
			create_surface(width, height);
			fill(red, green, blue);
		}
		
		/**
		 * Constructs a new Sprite object.
		 * The Sprite is created with the given dimenions.
		 * The Sprite is filled in with the given greyscale shade.
		 */
		Sprite(int width, int height, int brightness) noexcept {
			create_surface(width, height);
			fill(brightness, brightness, brightness);
		}
		
		/**
		 * Constructs a new Sprite object.
		 * The Sprite is created with the given dimenions.
		 * The Sprite is filled in with the given colour.
		 * Uses predefined colours.
		 */
		Sprite(int width, int height, Colour colour) noexcept {
			create_surface(width, height);
			fill(colour);
		}
		
		/**
		 * Constructs a new Sprite object.
		 * The Sprite is loaded from the BMP file passed in
		 *   string form and is not scaled.
		 */
		Sprite(const std::string& source) noexcept {
			surface = SDL_LoadBMP(source.c_str());
			allocated = true;
		}
		
		/**
		 * Constructs a new Sprite object.
		 * The Sprite is loaded from the BMP file passed in
		 *   string form and scaled to the given dimensions.
		 */
		Sprite(const std::string& source, int width, int height) noexcept {
			SDL_Surface* raw_surface = SDL_LoadBMP(source.c_str());
			create_surface(width, height);
			SDL_BlitScaled(raw_surface, nullptr, surface, nullptr);
			SDL_FreeSurface(raw_surface);
		}
		
		/**
		 * Copying a sprite can lead to double deallocation
		 *   and should not be performed.
		 */
		Sprite(const Sprite&) = delete;
		
		/**
		 * Sprites can be moved safely.
		 */
		Sprite(Sprite&& sprite) noexcept {
			operator=(std::move(sprite));
		}
		
		/**
		 * Frees the mmeory dynamically allocated to the surface
		 *   if it was allocated in this class.
		 */
		~Sprite() noexcept {
			destroy_surface();
		}
		
		/**
		 * Initialises the sprite with the given surface.
		 */
		Sprite& operator=(SDL_Surface* surf) noexcept {
			destroy_surface();
			surface = surf;
			
			return *this;
		}
		
		/**
		 * Copying a sprite can lead to double deallocation
		 *   and should not be performed.
		 */
		Sprite& operator=(const Sprite&) = delete;
		
		/**
		 * Sprites can be moved safely.
		 */
		Sprite& operator=(Sprite&& sprite) noexcept {
			destroy_surface();
			surface = sprite.surface;
			allocated = sprite.allocated;
			sprite.allocated = false;
			
			return *this;
		}
		
		/**
		 * Returns the width of the sprite.
		 */
		int get_width() const noexcept {
			return surface->w;
		}
		
		/**
		 * Returns the height of the sprite.
		 */
		int get_height() const noexcept {
			return surface->h;
		}
		
		/**
		 * Fills in the sprite with the given RGB colour.
		 */
		void fill(int red, int green, int blue) noexcept {
			SDL_FillRect(
				surface, nullptr,
				SDL_MapRGB(surface->format, red, green, blue)
			);
		}
		
		/**
		 * Fills in the sprite with a grayscale shade.
		 */
		void fill(int brightness) noexcept {
			fill(brightness, brightness, brightness);
		}
		
		/**
		 * Fills in the sprite with a predefined colour.
		 */
		void fill(Colour colour = BLACK) noexcept {
			switch (colour) {
				case BLACK:
					fill(0, 0, 0);
					break;
				
				case RED:
					fill(0xff, 0, 0);
					break;
					
				case GREEN:
					fill(0, 0xff, 0);
					break;
					
				case BLUE:
					fill(0, 0, 0xff);
					break;
					
				case YELLOW:
					fill(0xff, 0xff, 0);
					break;
					
				case CYAN:
					fill(0, 0xff, 0xff);
					break;
					
				case MAGENTA:
					fill(0xff, 0, 0xff);
					break;
				
				case WHITE:
					fill(0xff, 0xff, 0xff);
					break;
			}
		}
		
		/**
		 * Fills in the sprite in the area defined by the given rectangle.
		 */
		void fill(const Rectangle& rectangle, int red, int green, int blue) noexcept {
			SDL_FillRect(
				surface, rectangle.get(),
				SDL_MapRGB(surface->format, red, green, blue)
			);
		}
		
		/**
		 * Fills in the sprite in the area defined by the given rectangle.
		 * The sprite is filled in with a grayscale shade.
		 */
		void fill(const Rectangle& rectangle, int brightness) noexcept {
			fill(rectangle, brightness, brightness, brightness);
		}
		
		/**
		 * Fills in the sprite in the area defined by the given rectangle.
		 * Uses predefined colours.
		 */
		void fill(const Rectangle& rectangle, Colour colour = BLACK) noexcept {
			switch (colour) {
				case BLACK:
					fill(rectangle, 0, 0, 0);
					break;
				
				case RED:
					fill(rectangle, 0xff, 0, 0);
					break;
					
				case GREEN:
					fill(rectangle, 0, 0xff, 0);
					break;
					
				case BLUE:
					fill(rectangle, 0, 0, 0xff);
					break;
					
				case YELLOW:
					fill(rectangle, 0xff, 0xff, 0);
					break;
					
				case CYAN:
					fill(rectangle, 0, 0xff, 0xff);
					break;
					
				case MAGENTA:
					fill(rectangle, 0xff, 0, 0xff);
					break;
				
				case WHITE:
					fill(rectangle, 0xff, 0xff, 0xff);
					break;
			}
		}
		
		/**
		 * Fills in the sprite in the area defined by the given circle.
		 */
		void fill(const Circle& circle, int red, int green, int blue) noexcept {
			for (int i = 0; i < surface->w; i++) {
				for (int j = 0; j < surface->h; j++) {
					Rectangle rectangle(i, j, 1, 1);
					
					if (circle.contains(rectangle.get_point())) {
						fill(rectangle, red, green, blue);
					}
				}
			}
		}
		
		/**
		 * Fills in the sprite in the area defined by the given circle.
		 * The sprite is filled in with a grayscale shade.
		 */
		void fill(const Circle& circle, int brightness) noexcept {
			fill(circle, brightness, brightness, brightness);
		}
		
		/**
		 * Fills in the sprite in the area defined by the given circle.
		 * Uses predefined colours.
		 */
		void fill(const Circle& circle, Colour colour = BLACK) noexcept {
			switch (colour) {
				case BLACK:
					fill(circle, 0, 0, 0);
					break;
				
				case RED:
					fill(circle, 0xff, 0, 0);
					break;
					
				case GREEN:
					fill(circle, 0, 0xff, 0);
					break;
					
				case BLUE:
					fill(circle, 0, 0, 0xff);
					break;
					
				case YELLOW:
					fill(circle, 0xff, 0xff, 0);
					break;
					
				case CYAN:
					fill(circle, 0, 0xff, 0xff);
					break;
					
				case MAGENTA:
					fill(circle, 0xff, 0, 0xff);
					break;
				
				case WHITE:
					fill(circle, 0xff, 0xff, 0xff);
					break;
			}
		}
		
		/**
		 * Blits the given sprite to this one.
		 * The given sprite is scaled to match the size of this one.
		 */
		void blit(const Sprite& sprite) noexcept {
			SDL_BlitScaled(sprite.surface, nullptr, surface, nullptr);
		}
		
		/**
		 * Blits the given sprite to this one.
		 * The top-left corner of the given sprite is blitted to
		 *   the co-ordinates given.
		 * No scaling is performed.
		 */
		void blit(const Sprite& sprite, int x, int y) noexcept {
			SDL_Rect rectangle;
			rectangle.x = x;
			rectangle.y = y;
			SDL_BlitSurface(sprite.surface, nullptr, surface, &rectangle);
		}
		
		/**
		 * Blits the given sprite to this one.
		 * The top-left corner of the given sprite is blitted to
		 *   the coordinates of the given Point.
		 * No scaling is performed.
		 */
		void blit(const Sprite& sprite, const Point& point) noexcept {
			blit(sprite, point.get_x(), point.get_y());
		}
		
		/**
		 * Blits the given sprite to this one.
		 * The top-left corner of the given sprite is blitted to the
		 *   coordinates of the top-left vertex of the given Rectangle.
		 * No scaling is performed.
		 */
		void blit(const Sprite& sprite, const Rectangle& rectangle) noexcept {
			blit(sprite, rectangle.get_point());
		}
		
		/**
		 * Blits the given sprite to this one.
		 * The centre of the given sprite is blitted in the
		 *   given position.
		 * The position is a ratio of the size of this sprite.
		 * To blit to the centre, one should use 0.5 as x and y.
		 * No scaling is perfomed.
		 */
		void blit(const Sprite& sprite, double x, double y) noexcept {
			blit(
				sprite,
				static_cast<int>(surface->w * x - sprite.surface->w / 2),
				static_cast<int>(surface->h * y - sprite.surface->h / 2)
			);
		}
		
	private:
		/**
		 * Dynamically allocates a new surface with the given dimensions.
		 * If a surface was already dynamically allocated, it is freed.
		 */
		void create_surface(int width, int height) noexcept {
			if (allocated) {
				SDL_FreeSurface(surface);
			}
			
			surface = SDL_CreateRGBSurface(
				0, width, height, SURFACE_DEPTH,
				SURFACE_MASKS[BYTE_ORDER][0], SURFACE_MASKS[BYTE_ORDER][1],
				SURFACE_MASKS[BYTE_ORDER][2], SURFACE_MASKS[BYTE_ORDER][3]
			);
			
			allocated = true;
		}
		
		/**
		 * Destroys the surface if it was allocated.
		 */
		void destroy_surface() noexcept {
			if (allocated) {
				SDL_FreeSurface(surface);
				allocated = false;
			}
		}
		
		static constexpr int BYTE_ORDER                 // Byte ordering of the surface pixels.
			= SDL_BYTEORDER != SDL_BIG_ENDIAN; 
		static constexpr int SURFACE_DEPTH = 32;        // The number of bits per pixel.
		static constexpr Uint32 SURFACE_MASKS[2][4] = { // The position of bits for RGBA.
			{
				0xff000000,
				0x00ff0000,
				0x0000ff00,
				0x000000ff
			},
			{
				0x000000ff,
				0x0000ff00,
				0x00ff0000,
				0xff000000
			}
		};
		
		SDL_Surface* surface;   // The surface containing the pixel data of the sprite.
		bool allocated = false; // True if the surface's memory was allocated in this class.
};

/**
 * A class that manages the video system.
 * Each instance of this class corresponds with a window.
 * Instances of this class are not copiable, but are movable.
 */
class Display {
	public:
		/**
		 * Makes a window with the given dimensions and no title.
		 * Passing 0 as both the width and height makes
		 *   a "windowed fullscreen"-style window.
		 */
		Display(int width = 0, int height = 0) noexcept {
			if (!width && !height) {
				SDL_DisplayMode display_mode;
				SDL_GetDesktopDisplayMode(0, &display_mode);
				width = display_mode.w;
				height = display_mode.h;
			}
			
			create_window("", width, height, SDL_WINDOW_SHOWN);
		}
		
		/**
		 * Makes a window with the given title and dimensions.
		 * Passing 0 as both the width and height makes
		 *   a "windowed fullscreen"-style window.
		 */
		Display(const std::string& title, int width = 0, int height = 0) noexcept {
			if (!width && !height) {
				SDL_DisplayMode display_mode;
				SDL_GetDesktopDisplayMode(0, &display_mode);
				width = display_mode.w;
				height = display_mode.h;
			}
			
			create_window(title, width, height, SDL_WINDOW_SHOWN);
		}
		
		/**
		 * Constructs a new Display object from the given window.
		 * The window is not destroyed when this object is destroyed
		 *   and is the responsibility of the window's creator.
		 * For this reason, this constructor is not recommended.
		 */
		Display(SDL_Window* win) noexcept {
			window = win;
			sprite = std::make_unique<Sprite>(SDL_GetWindowSurface(window));
		}
		
		/**
		 * Display objects should not be copied.
		 * Copying can cause the window to be destroyed prematurely or twice.
		 */
		Display(const Display&) = delete;
		
		/**
		 * Display objects can be moved safely.
		 */
		Display(Display&& display) noexcept {
			operator=(std::move(display));
		}
		
		/**
		 * Destroys the window associated with the object if
		 *   the memory for it was allocated by this object.
		 * Frees the memory allocated to the Sprite object.
		 */
		~Display() noexcept {
			destroy_window();
		}
		
		/**
		 * Display objects should not be copied.
		 * Copying can cause the window to be destroyed prematurely or twice.
		 */
		Display& operator=(const Display&) = delete;
		
		/**
		 * Display objects can be moved safely.
		 */
		Display& operator=(Display&& display) noexcept {
			destroy_window();
			window = display.window;
			sprite = std::move(display.sprite);
			allocated = display.allocated;
			display.allocated = false;
			
			return *this;
		}
		
		/**
		 * Initialises the display with the given window.
		 * The window is not destroyed when this object is destroyed
		 *   and is the responsibility of the window's creator.
		 * For this reason, this use of this method is not recommended.
		 */
		Display& operator=(SDL_Window* win) noexcept {
			destroy_window();
			window = win;
			sprite = std::make_unique<Sprite>(SDL_GetWindowSurface(window));
			
			return *this;
		}
		
		/**
		 * Updates the window's surface.
		 */
		void update() noexcept {
			SDL_UpdateWindowSurface(window);
		}
		
		/**
		 * Returns a reference to the window's sprite.
		 * Allows for the sprite to be manipulated.
		 */
		Sprite& get_sprite() noexcept {
			return *sprite;
		}
		
		/**
		 * Retuens a constant reference to the window's sprite.
		 * Allows for the sprite's dimensions to be checked.
		 */
		const Sprite& get_sprite() const noexcept {
			return *sprite;
		}
		
	private:
		/**
		 * Creates the window and its sprite.
		 * Marks the window as self-allocated, which
		 *   means that the window will be destroyed
		 *   with this object.
		 */
		void create_window(
			const std::string& title,
			int width,
			int height,
			Uint32 flags
		) noexcept {
			window = SDL_CreateWindow(
				title.c_str(),
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				width,
				height,
				flags
			);
			sprite = std::make_unique<Sprite>(SDL_GetWindowSurface(window));
			allocated = true;
		}
		
		/**
		 * Destroys the window if the object allocated the memory for it.
		 */
		void destroy_window() noexcept {
			if (allocated) {
				SDL_DestroyWindow(window);
				allocated = false;
			}
		}
		
		SDL_Window* window;             // The window for the display.
		std::unique_ptr<Sprite> sprite; // The window's surface's sprite.
		bool allocated = false;         // True if this class allocated memory for the window.
};

/**
 * A class that manages the audio system.
 * Each instance of this class corresponds to an audio clip.
 */
class Audio {
	public:
		/**
		 * Loads an audio clip from the given source.
		 * Can requeue whenever one wishes to do so.
		 * The audio is unpaused by default.
		 */
		Audio(const std::string& source) noexcept {
			load(source);
			SDL_PauseAudioDevice(audio_device, false);
		}
		
		/**
		 * Loads an audio clip from the given source.
		 * Stores the length of the song in seconds for requeuing.
		 * The audio is unpaused by default.
		 */
		Audio(const std::string& source, double l) noexcept {
			load(source);
			SDL_PauseAudioDevice(audio_device, false);
			length = l;
		}
		
		/**
		 * Audio instances are not safe to be copied.
		 */
		Audio(const Audio&) = delete;
		
		/**
		 * Audio instances are safe to be moveed.
		 */
		Audio(Audio&& audio) noexcept {
			operator=(std::move(audio));
		}
		
		/**
		 * Frees all memory dynamically allocated to this object.
		 */
		~Audio() noexcept {
			free_audio();
		}
		
		/**
		 * Audio instances are not safe to be copied.
		 */
		Audio& operator=(const Audio&) = delete;
		
		/**
		 * Audio instances are safe to be moved.
		 */
		Audio& operator=(Audio&& audio) noexcept {
			// Memory for this object is freed.
			free_audio();
			
			// Data is moved.
			audio_device = audio.audio_device;
			audio_buffer = audio.audio_buffer;
			audio_length = audio.audio_length;
			last_queue = audio.last_queue;
			length = audio.length;
			paused = audio.paused;
			last_pause = audio.last_pause;
			allocated = audio.allocated;
			
			// The given instance no longer frees its memory.
			audio.allocated = false;
			
			return *this;
		}
		
		/**
		 * Sets the audio clip to play.
		 * Manages the queue timer to account for the time paused.
		 */
		void play() noexcept {
			if (paused) {
				last_queue += Timer::time() - last_pause;
				paused = false;
				SDL_PauseAudioDevice(audio_device, false);
			}
		}
		
		/**
		 * Sets the audio clip to pause.
		 * Stores the time of pausing.
		 */
		void pause() noexcept {
			if (!paused) {
				SDL_PauseAudioDevice(audio_device, true);
				paused = true;
				last_pause = Timer::time();
			}
		}
		
		/**
		 * Queues the audio to play after the current audio clip stops playing.
		 */
		void queue() noexcept {
			if (queuable()) {
				SDL_QueueAudio(audio_device, audio_buffer, audio_length);
				last_queue = Timer::time();
			}
		}
		
		/**
		 * Returns true if the audio is paused.
		 */
		bool pause_check() const noexcept {
			return paused;
		}
		
		/**
		 * Plays if the audio is paused.
		 * Pauses if the audio is playing.
		 */
		void pause_switch() noexcept {
			if (paused) {
				play();
			}
			
			else {
				pause();
			}
		}
		
		/**
		 * Returns true if the queue() method can queue audio.
		 */
		bool queuable() const noexcept {
			return !last_queue || !length || Timer::time() > last_queue + length;
		}
		
	private:
		/**
		 * Loads the song at the given source.
		 */
		void load(const std::string& source) noexcept {
			SDL_AudioSpec audio_spec;
			SDL_LoadWAV(source.c_str(), &audio_spec, &audio_buffer, &audio_length);
			audio_device = SDL_OpenAudioDevice(nullptr, false, &audio_spec, nullptr, 0);
			allocated = true;
		}
	
		/**
		 * Closes the associated audio device.
		 * Frees the audio buffer.
		 */
		void free_audio() noexcept {
			if (allocated) {
				SDL_CloseAudioDevice(audio_device);
				SDL_FreeWAV(audio_buffer);
			}
		}
	
		SDL_AudioDeviceID audio_device;
		Uint8* audio_buffer;
		Uint32 audio_length;
		double last_queue = 0;
		double length = 0;
		bool paused = false;
		double last_pause;
		bool allocated = false;
};

/**
 * A class that pairs the given Sprite with a Rectangle
 *   constructed for it.
 * The Sprite and Rectangle can be manipulated
 *   individually, but there a methods that use
 *   both objects in tandem.
 */
class Button {
	public:
		/**
		 * Constructs a new Button object from given Sprite.
		 * The Rectangle is constructed at the given position
		 *   and sets the dimensions to the sprite's dimensions.
		 */
		Button(std::unique_ptr<Sprite>&& s, int x = 0, int y = 0) noexcept {
			sprite = std::move(s);
			rectangle = std::make_unique<Rectangle>(
				x, y, sprite->get_width(), sprite->get_height()
			);
		}
		
		/**
		 * Constructs a new Button object from the given Sprite.
		 * The Rectangle is constructed with its dimensions set
		 *   to the sprite's dimensions.
		 * The Rectangle's position is set to mirror the effects
		 *   of Sprite::blit(const Sprite&, double, double).
		 */
		Button(
			std::unique_ptr<Sprite>&& s,
			const Sprite& stemplate,
			double x = 0.5,
			double y = 0.5
		) noexcept {
			sprite = std::move(s);
			rectangle = std::make_unique<Rectangle>(
				static_cast<int>(stemplate.get_width() * x - sprite->get_width() / 2),
				static_cast<int>(stemplate.get_height() * y - sprite->get_height() / 2),
				sprite->get_width(),
				sprite->get_height()
			);
		}
		
		/**
		 * Blits the Button's sprite to the given sprite using
		 *   the Button's Rectangle.
		 */
		void blit_to(Sprite& s) const noexcept {
			s.blit(*sprite, rectangle->get_x(), rectangle->get_y());
		}
		
		/**
		 * Returns a reference to the button's sprite.
		 */
		Sprite& get_sprite() noexcept {
			return *sprite;
		}
		
		/**
		 * Returns a constant reference to the button's sprite.
		 */
		const Sprite& get_sprite() const noexcept {
			return *sprite;
		}
		
		/**
		 * Returns a reference to the button's rectangle.
		 */
		Rectangle& get_rectangle() noexcept {
			return *rectangle;
		}
		
		/**
		 * Returns a constant reference to the button's rectangle.
		 */
		const Rectangle& get_rectangle() const noexcept {
			return *rectangle;
		}
	
	private:
		std::unique_ptr<Sprite> sprite;
		std::unique_ptr<Rectangle> rectangle;
};

/**
 * A class that manages the rendering of the sprites of
 *   characters and numbers to other sprites.
 * The characters and numbers are monospaced and only
 *   capital numbers are available.
 */
template<int N = LETTERS + NUMBERS>
class Renderer {
	public:
		/**
		 * Constructs a new Renderer object.
		 * Sprites are created for each letter and number
		 *   that has a source passed.
		 * The sources should be an array of strings and the count
		 *   should be the number of strings passed.
		 * The array of sources should start with the letters
		 *   in alphabetical order and then the numbers in
		 *   ascending order (A-Z then 0-9).
		 * The Boolean, numbers_first, indicates that the numbers
		 *   come before the letters in the array.
		 * An empty string can be used to not load a specific character.
		 */
		Renderer(
			const std::array<std::string, N>& sources,
			bool numbers_first = false
		) noexcept {
			load_sprites(sources, N, numbers_first);
		}
	
		/**
		 * Returns a sprite that is a rendering of the passed string.
		 * The size (in pixels) of the characters must be specified.
		 * The text is converted to uppercase.
		 */
		Sprite render(const std::string& text, int width, int height) const noexcept {
			int length = text.length();
			Sprite rendering(length * width, height);
			
			for (int i = 0; i < length; i++) {
				char character = text[i];
				
				// The character is converted to uppercase.
				if ('a' <= character && character <= 'z') {
					character -= 0x20;
				}
				
				// A letter is rendered
				if ('A' <= character && character <= 'Z') {
					Sprite temporary(width, height);
					temporary.blit(*letters[character - 'A']);
					rendering.blit(temporary, i * width, 0);
				}
				
				// A number is rendered
				else if ('0' <= character && character <= '9') {
					Sprite temporary(width, height);
					temporary.blit(*numbers[character - '0']);
					rendering.blit(temporary, i * width, 0);
				}
			}
			
			return rendering;
		}
	
	private:
		/**
		 * Constructs sprites for the given characters.
		 */
		void load_sprites(
			const std::array<std::string, N>& sources,
			int count,
			bool numbers_first
		) noexcept {
			// Constructs the numbers first.
			if (numbers_first) {
				load_numbers(sources, 0, count);
				load_letters(sources, NUMBERS, count - NUMBERS);
			}
			
			// Constructs the letters first.
			else {
				load_letters(sources, 0, count);
				load_numbers(sources, LETTERS, count - LETTERS);
			}
		}
		
		/**
		 * Constructs sprites for the given numbers.
		 */
		void load_numbers(
			const std::array<std::string, N>& sources,
			int offset,
			int count
		) noexcept {
			for (int i = 0; i < NUMBERS; i++) {
				// The sprite is loaded if the source was given.
				if (i < count && sources[i + offset] != "") {
					numbers[i] = std::make_unique<Sprite>(sources[i + offset]);
				}
				
				// Else, an empty sprite is loaded.
				else {
					numbers[i] = std::make_unique<Sprite>();
				}
			}
		}
		
		/**
		 * Constructs sprites for the given letters.
		 */
		void load_letters(
			const std::array<std::string, N>& sources,
			int offset,
			int count
		) noexcept {
			for (int i = 0; i < LETTERS; i++) {
				// The sprite is loaded if the source was given.
				if (i < count && sources[i + offset] != "") {
					letters[i] = std::make_unique<Sprite>(sources[i + offset]);
				}
				
				// Else, an empty sprite is loaded.
				else {
					letters[i] = std::make_unique<Sprite>();
				}
			}
		}
		
		std::array<std::unique_ptr<Sprite>, LETTERS> letters;
		std::array<std::unique_ptr<Sprite>, NUMBERS> numbers;
};

/**
 * Manages a separate thread of execution.
 * Useful for multi-threading, which allows multiple
 *   processes to be performed in tandem with each other
 *   boosting the computational efficiency of the program.
 * This is for use with 32-bit libraries, as they do not
 *   support std::thread.
 * If one uses a 64-bit library, use std::thread instead.
 */
class Thread {
	public:
		/**
		 * Creates a new thread of execution.
		 * The thread calls the function passed, which should
		 *   be of the type int function(void* data).
		 * The data argument is the data that will be passed
		 *   to the thread's function.
		 */
		Thread(SDL_ThreadFunction function, void* data) noexcept {
			thread = SDL_CreateThread(function, nullptr, data);
		}
		
		/**
		 * Instances of this class are not safe to copy.
		 */
		Thread(const Thread&) = delete;
		
		/**
		 * Instances of this class are safe to move.
		 * Moving is not recommended, as the thread must
		 *   for its function to return before taking the
		 *   value of the given thread.
		 */
		Thread(Thread&& t) noexcept {
			operator=(std::move(t));
		}
		
		/**
		 * If the thread has not returned by the end of this
		 *   object's lifetime, it is waited for.
		 */
		~Thread() noexcept {
			wait();
		}
		
		/**
		 * Instances of this class are not safe to copy.
		 */
		Thread& operator=(const Thread&) = delete;
		
		/**
		 * Instances of this class are safe to move.
		 * Moving is not recommended, as the thread must
		 *   for its function to return before taking the
		 *   value of the given thread.
		 */
		Thread& operator=(Thread&& t) noexcept {
			wait();
			thread = t.thread;
			t.thread = nullptr;
			
			return *this;
		}
		
		/**
		 * Waits for the thread to return and returns its exit code.
		 * If the thread is null, nothing happens and -1 is returned.
		 */
		int wait() noexcept {
			int code = -1;
			
			if (thread) {
				SDL_WaitThread(thread, &code);
				thread = nullptr;
			}
			
			return code;
		}
	
	private:
		SDL_Thread* thread = nullptr; // The thread of execution.
};

/* CHANGELOG
     v0.1:
	   Added the Messenger, Server, Client, Sprite, Display, and Audio classes.
	   Added the Colour enumeration.
	   Added the sdl_init(), sdl_quit(), get_time(), and wait() functions.
	 v0.2:
	   Added the System, Timer, and Events namespaces.
	   Renamed sdl_init() to initialised() and moved it to the System namespace.
	   Renamed sdl_quit() to terminate() and moved it to the System namespace.
	   Renamed get_time() to time() and moved to to the Timer namespace.
	   Moved wait() to the Timer namespace.
	 v0.3:
	   Added the Point and Rectangle classes.
	   Changed Sprite::fill() from using SDL_Rect to using Rectangle.
	 v0.3.2:
	   Added the System::version() and System::info() methods.
	 v0.4:
	   Added the Thread class.
	 v0.5:
		Added the Shape, Circle, and Button classes.
		Made Rectangle a derived class of Shape.
		Moved Rectangle::click() and Rectangle::unclick() to Shape.
		Added the Circle overloads of the Sprite::fill() methods.
		Deprecated the Thread class.
	 v0.6:
	   Added the Renderer class.
	 v0.6.1:
	   Changed the Sprite and Display classes to no longer be copiable.
	 v0.6.1.1:
	   Fixed Renderer::render().
	 v0.6.2:
	   Added Sprite::destroy_surface() and Display::destroy_window().
	   Fixed a memory leak in move assignment and construction of Sprite and Display objects.
	 v0.6.3:
	   Added the changelog.
	 v0.6.4:
	   Added the System::command() function.
	 v0.6.4.1:
	   Changed LETTERS and NUMBERS from macros to constant expressions.
	 v0.6.4.2:
	   Added warnings for Events::unclick() and Shape::unclick().
	 v.0.6.4.3:
	   Changed SDL_AND_NET_VERSION from const to constexpr.
	   Changed Sprite::BYTE_ORDER from const to constexpr.
	   Change Sprite::SURFACE_DEPTH from const to constexpr.
	 v0.6.5:
	   Changed the Renderer class to use std::array.
	   Changed the Renderer class to be templated.
	   Made Renderer::load_sprites() private.
	   Added the const version of Display::get_sprite().
	 v0.6.5.1:
	   Fixed Renderer::load_numbers() and Renderer::load_letters().
	 v0.6.6:
	   Added a Sprite::blit() overload for Rectangle.
	   Added the const version of Button::get_sprite().
	 v0.6.7:
	   Added the Rectangle::set() method that uses a sprite template.
	 v0.7:
	   Removed the Thread class.
	   Made Audio instances non-copiable, but movable.
	   Added Audio::queuable().
	 v0.8:
	   Restored the Thread class with no deprecation status.
	   Made the Thread class non-copiable, but movable.
	 v0.8.1:
	   Added the Rectangle default constructor.
	 v0.8.2:
	   Added the Timer::cureent() function.
	 v0.8.3:
	   Added the const version of Button::get_rectangle().
	 v0.8.4:
	   Added aliases for common scancodes in Events.
	   Converted System::VIDEO and System::AUDIO to constant expressions.
	   Converted Events::LEFT_CLICK, Events::MIDDLE_CLICK,
	     and Events::RIGHT_CLICK to constant expressions.
	 v0.8.5:
	   Made System::version() generic.
	 v1:
	   Added default arguments to multiple class constructors.
	   Added default arguments to some functions and methods.
	   Display's constructors no longer produce fullscreen windows.
	   Renderer now simply ignores invalid characters.
	   All functions and methods have been marked as noexcept.
	 v1.0.0.1:
	   Fixed a typo in System::info().
	 v1.0.0.2:
	   Fixed Point and Rectangle's integer constructors.
 */