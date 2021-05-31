# CPP

* C with class Bjarne Stroustrup developed
* Version
  * C++98: firht standard
  * C++11: lambdas, auto type deduction, list initialization, smart pointers, move semantics
  * C++14

> Terms

* Translation unit: ultimate input to a C or C++ compiler from which an object file is generated
  * In casual usage it is sometimes referred to as a compilation unit

* Module: header that is also a translation unit
  * compiled separately and only once
  * plugins or optional components that user may choose to be loaded or not

> Memory

* low memory address as chart goes down
* Memory
  * Heap
    * Large free pool of memory
    * Must allocate and deallocate
  * Stack
    * local variables declared inside a function lives until terminates
    * size of stack-frame is calculated when compiling

![Memory](images/20210214_024443.png)

```cpp
#include <stdio.h>
int global = 3;
int main() {
  int i;
  char *str = "Hello";
  char arr[2] = "Hi";
  printf("global : %p \n", &global);  // 0x3e2300
  printf("i : %p \n", &i);            // 0x7fff9ebe5740
  printf("str : %p \n", str);         // 0x2339c0 → literal
  printf("arr : %p \n", arr);         // 0x7fff9ebe5750
}
```

> Reference

<https://modoocode.com/134>

## GCC

* .cpp [<.o>]: compile / link files (gcc -xc++ -lstdc++ -shared-libgcc)
* -c: Compile / assemble the source files, but do not link (create .o)
* -g: enable gdb
* -H: Show header includes and nesting depth
* -I `dir`: Search `dir` for include (headers)
* -l: link libraries
* -L: /path contains library files, .a, .so
* -MD: Create dependency
* -o `out`: preprocessed C source: stdout
* -rpath=dir: -Wl,-rpath aaa bbb -> gcc -Wl,aaa -Wl,bbb
  * Add a directory to the runtime library search path
  * used when linking an ELF executable with shared objects (dynamic linker can find the libraries)
  * All -rpath arguments are concatenated and passed to the runtime linker, which uses them to locate shared objects at runtime
* -std=c++11: 11 version
* -v: Verbose Mode
* -Wall / extra: enable all warning / extra warnings
* -Wfatal-errors: causes compiler to abort compilation on the first error occurred
* -Wpedantic / unused: warnings demanded by strict ISO C and C++ / unused type definitions
* /W4: all reasonable warnings
* -Wl,aaa,bbb: list of tokens as a space-separated list of arguments to the linker (ld aaa bbb)
* -x: Specify the language of the following input files

### Preprocess

* `#include <stdio.h>` read stdio.h and insert directyl to program text -> creates `.i` file

### Compile

* translates the text file hello.i into the text file hello.s like below
  * provides a common output language for different compilers for different high-level languages

```assembly
main:
  subq  $8,     %rsp
  movl  $.LC0,  %edi
  call  puts
  movl  $0,     %eax
  addq  $8,     %rsp
  ret
```

* copy constructor / assignment operator / destructor / default constructor (when no other constructor)

```sh
Preprossess  # Include header, expand Macro (default source.suffix.gch)
Compilation  # assembly code (default source.s;)
Assemble     # generate machine code (default source.o;)
Linking      # .o / .obj (+ .lib / .a / static library) → .exe (default a.out)
```

* ELF (Executable and linkable file)
  * use objdump and nm in terminal
  * Headers tells which (shared lib, exe, *.o file) and give location of the section / program headers
  ![ELF file](images/20210214_022453.png)

### Assemble

* assembler translates hello.s into machine language instructions
* packages them in a form aka relocatable object program, and stores the result in the object file hello.o

### Link

* A more complete description is available in the GCC
* create executable that is ready to be loaded into memory and executed by the system

* added by the linking process
* starts with lib followed by name

> Library

![Libary](images/20210214_022603.png)

* static library: set of routines, external functions and variables which are resolved in a caller at compile-time
  * copied into a target application by a compiler, linker, or binder
  * produce an object file and a stand-alone executable

```cpp
// g++ -shared -o librandom.so random.cpp
// g++ main.cpp -lrandom -L.
// ./a.out

// main.cpp
#include <iostream>
#include "random.h"

int main() { std::cout << get_random_number(); }

// random.cpp
#include "random.h"
int get_random_number(void) { return 4; }

// random.h
int get_random_number();
```

* Dynamic Linrary: Linking postponed until execution time → useful for libraries
  * stub replaces itself with address of routine, and executes routine
  * Window → .dll, Apple → dylib (Framework), Unix → so

![Static vs Dynamic linking](images/20210214_023228.png)

## Util

> algorithm

* template \<class T, class Compare\>

* InputIterator find(InputIterator first, InputIterator last, const T& val);
* bool is_sorted(): Check if sorted with given comparater
  * ForwardIterator first, ForwardIterator last
  * Compare comp
* ForwardIt find_if(): Returns It to first element in range [first, last) that satisfies policy
  * ForwardIt first, ForwardIt last: ranges to search from
  * ExecutionPolicy&& policy

{% tabs %}
{% tab title='cpp' %}

```cpp
#include <algorithm>
#include <vector>

using namepsace std;

// 1. filter divisor
copy_if(vec.begin(), vec.end(), back_inserter(new), [div](int x) { return (x % div) == 0; });
str2.erase(remove_if(str2.begin(), str2.end(), [](unsigned char x){return std::isspace(x);})

// 2. fill
void fill (ForwardIterator first, ForwardIterator last, const T& val)
char flags[26][80];
fill(&flags[0][0], &flags[0][0] + sizeof(flags) / sizeof(flags[0][0]), 0 );      // fill 2d array
```

{% endtab %}
{% endtabs %}

> numeric

* adjacent_difference(): Compute adjacent difference of range
* gcd(`a`, `b`) / lcm(`a`, `b`): compute gcd / lcm between two numbers (c++17)
* inner_product(): Compute cumulative inner product of range
* partial_sum(): Compute partial sums of range
* iota(ForwardIt first, ForwardIt last, T value): Store increasing sequence

> utility

* swap()
* make_pair()
* forward()
* move_if_noexcept()
* decival()

* types
  * pair
  * piecewise_construct_t

* namespace
  * rel_ops

> functional

{% tabs %}
{% tab title='cpp' %}

```cpp
#include <functional>
using namespace std;

struct Foo {
  Foo(int num) : num_(num) {}
  void print_add(int i) const { std::cout << num_+i << '\n'; }
  int num_;
};

void print_num(int i) {
  std::cout << i << '\n';
}

struct PrintNum {
  void operator()(int i) const {
    std::cout << i << '\n';
  }
};

// store a free function
std::function<void(int)> f_display = print_num;
f_display(-9);

// store a lambda
std::function<void()> f_display_42 = []() { print_num(42); };
f_display_42();

// store the result of a call to std::bind
std::function<void()> f_display_31337 = std::bind(print_num, 31337);
f_display_31337();

// store a call to a member function
std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
const Foo foo(314159);
f_add_display(foo, 1);
f_add_display(314159, 1);

// store a call to a data member accessor
std::function<int(Foo const&)> f_num = &Foo::num_;
std::cout << "num_: " << f_num(foo) << '\n';

// store a call to a member function and object
using std::placeholders::_1;
std::function<void(int)> f_add_display2 = std::bind( &Foo::print_add, foo, _1 );
f_add_display2(2);

// store a call to a member function and object ptr
std::function<void(int)> f_add_display3 = std::bind( &Foo::print_add, &foo, _1 );
f_add_display3(3);

// store a call to a function object
std::function<void(int)> f_display_obj = PrintNum();
f_display_obj(18);
```

{% endtab %}
{% endtabs %}

> variant

{% tabs %}
{% tab title='cpp' %}

```cpp
#include <iostream>
#include <memory>
#include <variant>

using namespace std;

class A {
 public:
  void a() { cout << "I am A" << endl; }
};

class B {
 public:
  void b() { cout << "I am B" << endl; }
};

variant<A, B> GetDataFromDB(bool is_a) {
  if (is_a)
    return A();
  return B();
}

int main() {
  auto v = GetDataFromDB(true);

  cout << v.index() << endl;  // 0
  get<A>(v).a();              // I am A  // same as get<0>(v).a()
}
```

{% endtab %}
{% endtabs %}

> gnome

* g_print("%s", ...);
  * print

* g_strdup_printf("%s", line): Similar to C sprintf() function but safer
  * calculates the maximum space required and allocates memory to hold the result
  * returned string should be freed with g_free() when no longer needed, guaranteed to be non-NULL

## OpenGL

* Cross-language and cross-platform, open Graphics Library
* Render 3D graphics efficiently
* Extension Wrangler Library
* High-quality color images composed of geometric and image primitives
* Window / Operating system independent

> Terms

* Shader
  * shaders are small programs that rest on the GPU
  * These programs are run for each specific section of the graphics pipeline
  * In a basic sense, shaders are nothing more than programs transforming inputs to outputs
  * Shaders are also isolated programs in that they're not allowed to communicate with each other
  * the only communication they have is via their inputs and outputs

* GLU: part of OpenGL that supports more complex shapesL

* Keyboard
  * glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS

### gapi

![gapi](images/20210301_192949.png)

* Data objects do not hold actual data, only capture dependencies
* Operations consume and produce data objects

* cv::Mat: cv::GMat / cv::GMatDesc
* vector\<Obj\>: cv::GArray / cv::GArrayDesc
* G_API_NET(Class, API, Tag)
* G_API_OP(Class, Function, Name)
* G_TYPED_KERNEL

## glm

* OpenGL Mathematics
* A header only C++ math library
* Follow the OpenGL Shading Language (GLSL) specifications

* glm::vec3,glm::vec4, glm::mat3, glm::mat4: Vector / point / matrix (vector of vector)
* glm::vec3 a(1, 2, 3): A vector [1, 2, 3]
* glm::mat3 b(5): A 3x3 diagonal matrix diag(5)

> Methods

* detail::tvec3\<valType> glm::cross(): Returns the cross product of x and y
  * detail::tvec3\<valType> const &x, y: x and y are Floating-point scalar types

* genType::value_type glm::dot()
  * genType const &x, y: x and y are Floating-point vector types

* glm::length(): Returns the length of x, i.e., sqrt(x * x)
  * genType const &x

* glm::normalize(): Returns a vector in the same direction as x but with length of 1
  * genType const &x

* glm::translate(): Builds a translation 4 * 4 matrix created from 3 scalars
  * T x, T y, T z

* glm::scale()
  * glm::mat4 matrix
  * glm::vec3 scale_vector:  specifies the scale vector to the given each axis of the given vector

* glm::rotate()
  * glm::mat4 matrix
  * GLfloat angle: angle in radians,
  * glm::vec3 rotation_axis): specifies the axis to rotate around)

* void glBindTexture(): bind a named texture to a texturing target
  * GLenum target: ex) GL_TEXTURE_1D, GL_TEXTURE_2D
  * GLuint texture

* void glAttachShader(): Attaches a shader object to a program object
  * GLuint program
  * GLuint shader

* void glDetachShader(): Detaches a shader object from a program object to which it is attached
  * GLuint program,
  * GLuint shader

* glGetError(): location of error and clear the error flags
* gluErrorString(): parse the error message

{% tabs %}
{% tab title='cpp' %}

```cpp
// 1. Draw Triangle
glBegin(GL_TRIANGLES);
glVertex2f(-0.5f, -0.5f);
glVertex2f(0.0f, 0.5f);
glVertex2f(0.5f, -0.5f);
glEnd();
```

{% endtab %}
{% endtabs %}

### glfw

* Graphics Library Framework
* C++ library that handles creating windows and interacting with the windows
* Provide an OpenGL context such that we can draw in the window

* void glDrawArrays()
  * GLenum mode: GL_POINTS, GL_LINE_STRIP, GL_LINES, GL_TRIANGLES
  * GLint first: starting index in the enabled arrays
  * GLsizei count

* void glDrawElements()
  * GLenum mode: GL_POINTS, GL_LINE_STRIP, GL_LINES, GL_TRIANGLES
  * GLsizei count: Specifies the number of elements to be rendered
  * GLenum type: GL_UNSIGNED_BYTE, SHORT, INT
  * const GLvoid * indices: A pointer to the location where the indices are stored.

* glEnableVertexAttribArray(GLuint index);
  * void glGenBuffers()
  * GLsizei n: Specifies the number of buffer object names to be generated
  * GLuint * buffers: An array in which the generated buffer object names stored

* GLint glGetUniformLocation()
  * GLuint program: Specifies the program object to be queried
  * const GLchar *name: String containing the name of the queried uniform variable

* glLinkProgram(program);

* void glUniformMatrix4fv(): set values of a uniform variable for the current program object
  * GLint location
  * GLsizei count
  * GLboolean transpose
  * const GLfloat *value

* glValidateProgram(program);

* glVertexAttribPointer(): Define an array of generic vertex attribute data
  * GLuint index: Should be same as location in shader file
  * GLint size
  * GLenum type
  * GLboolean normalized: if normalization to 0 to 1 is needed
  * GLsizei stride: amount of bytes in each vertex (sizeof(struct))
  * const GLvoid * pointer: offset of each component within vertex

* void glTextureParameteri()
  * GLuint texture
  * GLenum pname
  * GLint param

{% tabs %}
{% tab title='cpp' %}

```cpp
blBindBuffer(GL_ARRAY_BUFFER, VBO);  // bind buffer to VAO
// 1. Populate data in VBO
blBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
glEnableVertexAttribArray(0);      // Create channel between VBO and shader
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

glGenBuffers(1, &EBO);           // Generate EBO
blBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);   // Bind buffer
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * indices.size(), indices.data(), GL_STATIC_DRAW);

// 2. COLOR
GLuint colorbuffer;
glGenBuffers(1, &colorbuffer);
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
```

{% endtab %}
{% endtabs %}

### sfml

* Consists system, window, graphics, network and audio
* g++ a.cpp -o a -lsfml-graphics -lsfml-window -lsfml-system
* using namespace sf;

* Event
  * Closed
  * LostFocus
  * GainedFocus
  * KeyPressed / TextEntered
  * Resized
  * MouseEntered / MouseLeft / MouseButtonPressed / MouseButtonReleased / MouseMoved

* Texture
  * create(200, 200): create 200x200 Empty image
  * loadFromFile("path_to_images", IntRect(10, 10, 32, 32)): 32x32 rectangle that starts at (10, 10)
  * setPosition(sf::Vector2f(10.f, 50.f));: absolute position
  * move(Vector2f(5.f, 10.f));: offset relative to the current position
  * sprite.setRotation(90.f);: absolute angle
  * sprite.rotate(15.f);: offset relative to the current angle
  * sprite.setScale(Vector2f(0.5f, 2.f));: absolute scale factor
  * sprite.scale(Vector2f(1.5f, 3.f));: factor relative to the current scale

* context
  * setRepeated([bool]): texture to be repeatedly tiled within a single sprite
  * setSmooth([bool]): makes pixel boundaries less visible
  * rotate(15.f);: offset relative to the current angle

* RenderWindow
  * create(VideoMode(w, h), "txt!");: create window size (w, h) with text
  * close() / isOpen(): is opened
  * clear() / draw(): display()  clear and draw sprite
  * pollEvent(event)

* Sprite
  * setRotation(90.f);: absolute angle
  * setTexture(texture): set texture
  * setPosition(x, y): set position
  * setColor(Color([R], [G], [B], [transparency]));

* Texture
  * loadFromFile(fn): load texture image
  * setString("t") / setCharacterSize(10): set string / size
  * setOrigin(x, y) / setPosition(x, y);: set position of text

* Text
  * setFillColor(Color::White);

{% tabs %}
{% tab title='cpp' %}

```cpp
// 1. keyboard
if (event.type == Event::TextEntered) {
  if (event.text.unicode < 128)
    cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << endl;
}

if (event.type == sf::Event::KeyPressed) {
  if (event.key.code == sf::Keyboard::Escape) {
    cout << "the escape key was pressed" << endl;
    cout << "control:" << event.key.control << endl;
    cout << "alt:" << event.key.alt << endl;
    cout << "shift:" << event.key.shift << endl;
  }
}

// 2. Mouse
Vector2i pos = Mouse::getPosition(app);            // get current position

if (event.type == sf::Event::MouseButtonPressed) {
  if (event.mouseButton.button == sf::Mouse::Right) {
    cout << "the right button was pressed" << endl;
    cout << "mouse x: " << event.mouseButton.x << endl;
    cout << "mouse y: " << event.mouseButton.y << endl;
  }
}
```

{% endtab %}
{% endtabs %}

## Gstreamer

![GStreamer](images/20210207_231800.png)

* [https://gstreamer.freedesktop.org/documentation/tutorials/basic/hello-world.html?gi-language=c](https://gstreamer.freedesktop.org/documentation/tutorials/basic/hello-world.html?gi-language=c)
* framework for creating multitype streaming media application for video, audio
* used to build media player supporting a variety of formats
* [+] pluggable components can be mixed into arbitrary pipelines, full-fledged video or audio editing app

* protocol handling: file, http, rtsp
* sources: alsa, v4l2
* formats: avi, mp4, ogg
* codecs: mp3, mpeg4, vorbis
* filters: converters, mixers, effects
* sinks: alsa, xvideo, tcp / udp

> Setup

* sudo apt-get install gtk+-3.0
* sudo apt-get install libgstreamer-plugins-base1.0
* sudo brew install gtk+-3.0 (mac)

* gcc file_name.c -o file_name `pkg-config --cflags --libs gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0`

> Terms

* pad
  * elements input and output, where you can connect other elements
  * viewed as plug or port on the element (restrict the type of data)

* bin: container for a collection of elements, mostly control a bin as if it were an element

* pipeline: a top-level bin provides a bus for application and manages synchronization for its children

* communication
  * buffer: objects for passing streaming data between elements
  * events: objects sent between elements which can travel upstream / downstream
  * messages: objects posted by elements on pipeline’s message bus
  * query: allow application to request information
  ![Communication](images/20210207_232135.png)

* Plugin
  * gst-plugins-base: exemplary set of elements
  * gst-plugins-good: set of good-quality plug-ins under LGPL
  * gst-plugins-ugly: set of good-quality plug-ins that might pose distribution problems
  * gst-plugins-bad: set of plug-ins that need more quality
  * gst-libav: set of plug-ins that wrap libav for decoding and encoding

> CLI

* gst-inspect-1.0
  * plugin_name: inspect plugin_name

* gst-launch-1.0
  * -e, --eos-on-shutdown     # Force EOS on sources before shutting the pipeline down
  * export GST_DEBUG=5            # enable log
  * export GST_DEBUG=gvatracker:5 # enable log for specific

* src: do not accept data, only generate data (reading from disk or from a sound card)

* videotestsrc
  * pattern: smpte (0) / snow (1) / colors (24) – Colors
  * framerate=1/5

* filesrc: Read data from a file in the local file system

* multifilesrc: Reads buffers from sequentially named files
  * to use with an image decoder, use “caps” property or a capsfilter to force to caps containing a framerate

> Filter

* GstPad queue(GstPad)
  * specified by GstQueue:max-size-buffers, GstQueue:max-size-bytes GstQueue:max-size-time properties
  * Any attempt to push more buffers into queue will block pushing thread until more space becomes available

* h264parse: Parses H.264 streams

* timeoverlay: overlays the buffer timestamps of a video stream on top of itself

* pngdec: Decodes png images
  * If there is no framerate set on sink caps, it sends EOS after the first picture
  * src: video/x-raw
  * format (RGBA, RGB, ARGB64, GRAY8, GRAY16_BE), width,height
  * framerate

* sink: image/png

* vaapi264dec: decodes from H264 bitstreams to surfaces suitable for vaapisink or vaapipostproc elements
  * use installed VA-API back-end

* videoconvert: Convert video frames between a great variety of video formats

* video/x-raw

> Sink

* endpoints in a media pipeline (Disk writing, soundcard playback, and video output)

* fakesink: location=test.avi: save to video

* multifilesink
  * location=img%d.png
  * max-files: Max files to keep on disk. old files start to be deleted to make room for new ones

> No such element or plugin 'gvatracker'

* echo $GST_PLUGIN_PATH
* gst-inspect-1.0 gvatracker

> ERROR: from element /GstPipeline:pipeline0/GstH264Parse:h264parse0: Failed to parse stream

* gst-launch-1.0 -e multifilesrc location=/home/root/mot17/train/MOT17-02-SDP/yuv_raws/frame%d.yuv index=1 ! \
  h264parse ! vaapih264dec  !  fakesink sync=false

> WARNING: erroneous pipeline: could not link multifilesrc0 to videoconvert0

* gst-launch-1.0 -e multifilesrc location="/home/root/mot17/train/MOT17-02-SDP/yuv_raws/frame%d.yuv" \
  caps="image/yuv,framerate=(fraction)12/1" index=1  ! videoconvert ! fakesink sync=false

> ERROR: from element /GstPipeline:pipeline0/GstMultiFileSrc:multifilesrc0: Internal data stream error.
  Additional debug info:
  ../gstreamer-1.16.0/libs/gst/base/gstbasesrc.c(3072): gst_base_src_loop (): /GstPipeline:pipeline0/GstMultiFileSrc:multifilesrc0:
  streaming stopped, reason not-negotiated (-4)
  ERROR: pipeline doesn't want to preroll.

* Wrong multifilesrc location

```text
gst-launch-1.0 -e multifilesrc location=frame%d.yuv index=1  ! gvatracker profile=true !  fakesink sync=false
```

* GstBus: object responsible for delivering GstMessage packets in a first-in first-out way from streaming threads to application
  * marshall the messages between different threads
  * Get a message from a bus whose type matches message type mask types, waiting up to the specified timeout
  * discarding any messages that do not match the mask provided
  * with timeout 0, behaves like gst_bus_pop_filtered
  * with timeout GST_CLOCK_TIME_NONE, block until a matching message was posted on the bus

```text
GObject
    ╰──GInitiallyUnowned
        ╰──GstObject
            ╰──GstBus
```

* GstMessage _gst_bus_timed_pop_filtered()
  * GstBus_ bus,
  * GstClockTime timeout,
  * GstMessageType types)

* GstMap
  * gst_buffer_map(buffer)

* GstBin
  * gst_bin_get_by_name (GstBin _bin, const gchar_ name)
    * Gets the element with the given name from a bin recursing into child bins
    * Returns NULL if no element with the given name is found in the bin
    * MT safe. Caller owns returned reference
  * gst_bin_add_many (GST_BIN (pipeline), source, filter, sink, NULL);
  * gst_object_unref(gst_element)
  * g_warning ("Failed to link elements!");
  ![GstBin](images/20210208_012758.png)

* GstBuffer: Basic unit of data transfer in GStreamer
  * contain timing and offset along with other arbitrary metadata associated with GstMemory blocks that buffer contains
  * GstBuffer gst_buffer_new(): Creates a newly allocated buffer without any data
  * gstbuffer_make_writable(GstBuffer buffer): Returns a writable copy of buf, if source buffer is already writable
    * this will simply return the same buffer

* GstElement: abstract base class needed to construct an element that can be used in a GStreamer pipeline
  * contains GList of GstPad structures for all their input (sink) and output (source) pads

> State

* **GST_STATE_NULL**: No resources are allocated in this state, so, transitioning to it will free all resources
  * The element must be in this state when its refcount reaches 0 and it is freed

* GST_STATE_READY: element has allocated all of its global resources, that is, resources that can be kept within streams
  * You can think about opening devices, allocating buffers and so on
  * However, the stream is not opened in this state, so the stream positions is automatically zero
  * If stream was previously opened, it should be closed in READY, and position, properties and such should be reset

* GST_STATE_PAUSED: element has opened the stream, but is not actively processing it
  * element is allowed to modify a stream's position
  * read and process data and such to prepare for playback as soon as state is changed to PLAYING
  * it is not allowed to play the data which would make the clock run
  * PAUSED is the same as PLAYING but without a running clock
  * Elements going into the PAUSED state should prepare themselves for moving over to PLAYING state as soon as possible
  * Video or audio outputs would
  * Also, video sinks can already play the first frame since this does not affect the clock yet)
  * Autopluggers could use this same state transition to already plug together a pipeline
  * Most other elements, such as codecs or filters, do not need to explicitly do anything in this state, however
  * [ex] wait for data to arrive and queue it so they can play it right after the state change

* GST_STATE_PLAYING: element does exactly the same as in the PAUSED state, except that the clock now runs

* GstElement _gst_parse_launch (const gchar_ pipeline_description, GError ** error)
  * gst_element_link_many (source, filter, sink, NULL)
* gst_element_factory_make (factory_name, element_name)
  * name of the element is something you can use later on to look up the element in a bin
* gst_object_unref ()
  * unref, decrease reference count by 1
* gst_element_factory_find(factory, GST_ELEMENT_METADATA_KLASS)
* gst_element_factory_get_metadata()
* gst_element_get_name() / gst_element_set_name()

* gst_element_add_pad() / gst_element_remove_pad()
* gst_element_iterate_pads()
* gst_element_set_state ()
* gst_element_sync_state_with_parent ()

* GstPipeline
  ![Pipeline](images/20210208_012953.png)
  * chain of elements create pipeline, links are allowed when two pads are compatibles
  * element has one specific function (reading data from file, decoding data)
  * gst_pipeline_new ("my-pipeline");
    * create new pipeline

* GstPad
  * _gst_element_get_static_pad(): Retrieves pad from element by name, only retrieves already-existing (static) pads
    * GstElement_ element, const gchar * name
  * gst_pad_get_parent(): retrieve GstElement that owns the pad
  * GstParse()

```cpp
GObject
    ╰──GInitiallyUnowned
        ╰──GstObject
            ╰──GstPad
                ╰──GstProxyPad

#define GST_PARSE_ERROR gst_parse_error_quark ()   // get an error quark of parse subsystem
#define GST_TYPE_PARSE_CONTEXT (gst_parse_context_get_type())
```

* GstProbe: callback that can be attached to a pad
  * run in the pipeline's streaming thread context
  * one should usually avoid calling GUI-related functions from within a probe callback
  * nor try to change the state of the pipeline

* Dataprobe: Data probes notify you when there is data passing on a pad
  * GST_PAD_PROBE_TYPE_BUFFER
    * A buffer is pushed or pulled
  * gulong gst_pad_add_probe(GstPad * pad,
    * GstPadProbeType mask,
    * GstPadProbeCallback callback,
    * gpointer user_data,
    * GDestroyNotify destroy_data)
  * Be notified of different states of pads. callback is called for every state that matches mask
  * gst_pad_remove_probe()
    * remove callback

## Make

* Search GNUmakefile -> makefile -> Makefile
* Runs in a seperate shell

> Terms

```make
target … : prerequisites …
  recipe
```

* target: usually name of a file generated by a program | name of action to carry out
* prerequisite: file that is used as input to create the target
* recipe: an action that make carries out
  * @:: do nothing

* include `../Makefile`: include other makefile
* kits: project-agnostic and configuration-agnostic information about how to build code
  * [ex] compilers, vscode installation, toolchain file

* variant: compile option
  * Debug: disables optimizations and includes debug info
  * Release: Includes optimizations but no debug info
  * MinRelSize: Optimizes for size. No debug info
  * RelWithDebInfo: Optimizes for speed and includes debug info

* .PHONY: implicit rule search is skipped for .PHONY targets
* .PRECIOUS: Don’t get deleted even if it is an intermediate file
* .SILENT: make will not print recipe used to remake those files before executing them

> CLI

* <> c=hello: make with passing parameter which can be accessed $(c)
* all: convention (put all at top of the file)
* -f File: Reads FILE as the makefile
* -h: Displays the list of make
* -s: silent error
* -j $(proc): Set to number of core

```sh
# 1. Simple makefile file Structure
# ├── 00_macro.cpp
# ├── 01_primitives.cpp
# ├── 02_pointer.cpp
# ├── bin
# │   ├── 00_macro
# │   ├── 01_primitives
# │   ├── 02_pointer
# ├── common
# │   ├── common.hpp
# │   └── logger.hpp
# ├── data
# │   ├── fstream.txt
# │   └── thread.txt
# └── obj
#   ├── 00_macro.o
#   ├── 01_primitives.o
#   └── 02_pointer.o
# .
# ├── Makefile

SRC_DIR=.
OBJ_DIR=./obj
BIN_DIR=./bin

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
BINS := $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR/%.o))

CXX=g++
CXXFLAGS= -std=c++2a -Wall -o=bin
LDFLAGS=

all: $(BINS)         # if no .DEFAULT it runs first target
  @:

run: $(BIN_DIR)/$(basename $(filter-out run,$(MAKECMDGOALS)))
  @$(BIN_DIR)/$(basename $(filter-out $@,$(MAKECMDGOALS)))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
  $(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/%: $(OBJ_DIR)/%.o | $(BIN_DIR)
  $(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

$(BIN_DIR) $(OBJ_DIR):
  mkdir -p $@

.PHONY:     all run clean     # even if all run clean filename exists
.PRECIOUS:  $(OBJ_DIR)/%.o    # keep intermediate files

clean:
  rm -r $(BIN_DIR) $(OBJ_DIR)

# 2. cpp using PKG_CONFIG
export PKG_CONFIG_PATH="/usr/local/lib/pkgconfig"

$ g++ filename.cpp $(pkg-config --cflags --libs opencv)

CXX ?= g++
CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)
all: opencv_example
opencv_example: example.o; $(CXX) $< -o $@ $(LDFLAGS)
%.o: %.cpp; $(CXX) $< -o $@ $(CXXFLAGS)
clean: ; rm -f example.o opencv_example
```

## Cmake

{% tabs %}
{% tab title='cmake' %}

* CXX=clang++ cmake ..: pick compiler only once

* cmake
  * --help: help
  * --config Debug: (ex. Release, RelWithDebInfo, MinSizeRel)
  * --build build: equivalent to make
  * -D var:type=val: manipulate cache values
  * -U 'help*': remove variable from cache
  * -G "Unix Makefiles": Omitting will choose default generator
  * -j N: parallel builds on N cores
  * -S .: specify source directory
  * -t: pick a target
  * -U: remove variables from cache
  * -v: verbose
  * --trace: print every line of CMake run
  * --trace-source="fname": print in file
  * -B: build from source dir
  * -L: List option in human readable
  * -LH: Human Readable

```sh
# 1. opencv.sh
cmake -B build -DCMAKE_BUILD_TYPE=RELEASE \
  -DCMAKE_INSTALL_PREFIX=../install \
  -DBUILD_EXAMPLES=ON \
  -DOPENCV_GENERATE_PKGCONFIG=ON \
  -DBUILD_DOCS=ON \
  -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules \
  -DBUILD_EXAMPLES=ON
```

> CMake Error: Error processing

* -C option is for preloading cache
* -D for defining some var value
* cmake -CMAKE_TOOLCHAIN_FILE=/home/swt/work/Toolchain-ts7800-arm.cmake .

> CMake was unable to find a build program coressponding to "Unix Makefiles". CMAKE_MAKE_PROGRAM is not set.

* You probably need to select a different build tool
  * check toolchain file location

> file INSTALL cannot copy file

* " ~/build/x86_64/Release/lib/libname.so.1.0.1" to "/usr/local/lib/libname.so.1.0.1"

```cmake
# update cache
CMAKE_INSTALL_PREFIX:PATH=/usr/local

# when cmake
-CMAKE_INSTALL_PREFIX:PATH=/usr/local
```

> libopencv_dnn.so.4.5.1: undefined reference to `ngraph:

* check target_link_libraries

> ~/gcc/aarch64-ese-linux/real-ld: warning: libinference_engine.so, needed by ~/opencv/lib/libopencv_gapi.so.4.5.1, not found
  (try using -rpath or -rpath-link)

* Add Linker flag

```cmake
set (CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,/opt/openvino/deployment_tools/ngraph/lib")
```

> Reference

<https://www.youtube.com/watch?v=wP4cwAtU-g8>

{% endtab %}
{% endtabs %}

## CMake File

* CMakeCache.txt: store information for reuse on subsequent runs

> CMakeList.txt

* input to the CMake build system for building software packages
* describes how to build the code and where to install it to dependency
* 3.2 support reasonably all new, OS requires even newer
* CMAKE uses spaces as delimiter → put double quotes

* dependency
  * Generator: [(ex] Unix Makefiles, Ninja, Xcode)
  * in-source-build: store binary and src files in the same (DISCOURAGED → V.C.)
  * public dependency: A uses B in its interface (ex. A func has a param of a type in B)
  * private dependency: A uses B in its own internal implementation
  * interface dependency: A uses B

* lower case for function, Upper case is for variables → case insensitive

{% tabs %}
{% tab title='cmake' %}

```sh
# 1. Download
RUN CMAKE_INSTALLER=cmake-3.10.3.tar.gz \
    && wget https://cmake.org/files/v3.10/${CMAKE_INSTALLER} \
    && tar xvfz ${CMAKE_INSTALLER} \
    && cd ${CMAKE_INSTALLER%.tar.gz} \
    && source scl_source enable devtoolset-7 \
    && ./bootstrap --parallel=`nproc` \
    && make -j `nproc` install \
    && cd .. \
    && rm -rf ${CMAKE_INSTALLER} ${CMAKE_INSTALLER%.tar.gz}

# 2. Simple cpp
├── CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(same_folder)                            # Root CMAKE must have, set PROJECT_VERSION, PROJECT_NAME
add_definitions("-Wall -std=c++14")             # g++ -D option
add_executable(main main.cpp test.cpp)
├── main.cpp
├── test.cpp
└── test.h

# 3. splitted into src / include dir + external
.
├── CMakeLists.txt
cmake_minimum_required(VERSION 3.0.0)
project(tictactoe)
find_package( OpenCV REQUIRED )         # CMAKE_PREFIX_PATH=~/github/opencv/build
file(GLOB SOURCES "src/*.cpp")
add_executable(tictactoe ${SOURCES})
include_directories(include)
set(LIBS ${OpenCV_LIBS})
target_link_libraries( tictactoe ${LIBS} )
├── include
│   ├── board.h
│   ├── model.h
│   └── tictactoe.h
└── src
  ├── board.cpp
  ├── main.cpp
  ├── model.cpp
  └── tictactoe.cpp

# 4. Add resources
.
├── CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(example_project)

# 5. target definitions #########################################################
add_executable(example ${sources} ${data})
target_compile_options(example PUBLIC -std=c++1y -Wall -Wfloat-conversion)
target_include_directories(example PUBLIC src/main) # to include files relative to root of src directory with a <> pair
file(COPY ${data} DESTINATION resources) # copies resource files in build directory, to work with paths relative to executable

# dependencies ###############################################################
find_package(Boost 1.36.0 COMPONENTS filesystem system REQUIRED)
target_link_libraries(example PUBLIC ${Boost_LIBRARIES})

# testing ####################################################################
find_package(GTest)
if(GTEST_FOUND)
  add_executable(unit_tests ${sources_test} ${sources})
  # prevent collision with main. better by not adding source with main to testing target
  target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)
  set_target_properties(example PROPERTIES ENABLE_EXPORTS on)

  # use executable as link library, and inherit linker options / library dependencies from it, by adding as dependency.
  target_link_libraries(unit_tests PUBLIC
  ${GTEST_BOTH_LIBRARIES} example)
  target_include_directories(unit_tests PUBLIC
  ${GTEST_INCLUDE_DIRS}) # doesn't do anything on linux

endif()

# 6. library
├── CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(libarary)                               # shared (dynamic), Linking postponed until execution time (useful for libraries)
add_library(test SHARED test.hpp test.cpp)      # ldd main prints @rpath/libtest.dylib if SHARED  (static default)
add_executable(main main.cpp)
target_link_libraries(main test)
├── main.cpp
├── test.cpp
└── test.hpp

# 7. packaging ##################################################################
# all install commands get same destination. this allows us to use paths relative to executable.
install(TARGETS example DESTINATION example_destination)
# repeat of file copy instruction that copies resources in build dir, but here put in package.
install(DIRECTORY resources DESTINATION example_destination)

set(CPACK_PACKAGE_NAME "MyExample")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_MONOLITHIC_INSTALL 1) # save program into one complete piece
include(CPack)                  # This must be last
├── LICENSE
├── README.md
├── resources
│   └── resource1
└── src
  ├── main
  │   ├── main.cpp
  │   └── main.h
  └── test
    └── test.cpp

# 8. Hello subdirectory
.
├── CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(test)
add_subdirectory(test)
add_executable(main main.cpp)
target_link_libraries(main test)
├── errors.cpp
├── main.cpp
└── test
  ├── CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
add_library(test STATIC test.cpp)       # STATIC, SHARED, or MODULE may be given to specify type of library to be created
  ├── test.cpp
  └── test.h

# 9. subdirectory 2
├── CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(hello)
add_subdirectory(test)
add_subdirectory(main)                    # order is important
├── main
│   ├── CMakeLists.txt
add_executable(hello_main main.cpp)
target_link_libraries(hello_main hello_test)
│   └── main.cpp                          # #include <hello/test.hpp>
└── test
  ├── CMakeLists.txt
add_library(hello_test hello/test.cpp hello/test.hpp)
target_include_directories(hello_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_definitions(hello_test PUBLIC MODE=4)     # PUBLIC - all targets, INTERFACE - except cur, PRIVATE - only cur
  └── hello
    ├── test.cpp
    └── test.hpp
```

{% endtab %}
{% endtabs %}
