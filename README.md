# blBufferLIB

## What is it?

blBufferLIB is a header-only template library that defines the type ```blBuffer<T>``` as well as useful **circular iterators** and **circular reverse iterators**, which take a generic contiguous buffer and interpret it as an N-Dimensional space

- The blBuffer class can:

  - Hold its own contiguous data

  - Or *wrap* existing user supplied external contiguous data

    - That means that if you *wrap* for example an ```std::vector<T>``` with ```blBuffer<T>```, it would then allow the contiguous ```std::vector<T>``` array to be seen as an N-Dimensional buffer

- The buffer defines ```size(i)``` and ```length(i)``` functions which return the respective dimensional sizes/lengths as well as the ```size()``` andn ```length()``` functions which return the overall buffer length

- The buffer also defines specially named ```size``` functions such as ```rows```, ```cols```, ```pages```, ```height```, ```width```, ```depth``` for the first 3 dimensions

  - ```rows``` and ```height``` functions return the size of the 1st dimension
  - ```cols``` and ```width``` functions return the size of the 2nd dimension
  - ```pages``` and ```depth``` functions return the size of the 3rd dimension

- The blBuffer class defines access functions ```operator()``` and ```at``` functions as well as their **_circular_** counterparts such as ```circ_at``` so that the buffer's data, either internal or external, can be accessed with N-Dimensional sets of coordinates:

> For example:
```c++
// Here we create a 3d buffer of size (3 x 3 x 10)

blBufferLIB::blBuffer<double> myBuffer;
myBuffer.create(3,3,10);



// Here we access the second data point
// as if the buffer was a 1d-buffer
// even though we said it was a 3d buffer

auto dataPoint = myBuffer(2);



// Here we access a data point
// using 3d coordinates

auto dataPoint2 = myBuffer(0,2,3);



// Here we access a data point
// cicularly as if buffer was a
// 1d-buffer

auto dataPoint3 = myBuffer.circ_at(100023);



// Here we access a data point
// circularly using 3d coordinates

auto dataPoint3 = myBuffer.circ_at(1000,2231,124);



// Here we ask for the size/length
// of the 2nd dimensional

auto width = myBuffer.size(2);
```

The blBuffer class defines many additional abstract concepts that allow the user to do some advanced manipulation of data with little to no effort:

- It defines iterators for iterating through the entire data like a normal ```std::vector<T>```:

  - ```begin()```/```end()```
  
  - ```cbegin()```/```cend()```
  
  - ```rbegin()```/```rend()```
  
  - ```crbegin()```/```crend()```
  
- It defines *stl-algorithms-compatible* **_circular_iterators_** which can be used in *stl-like* algorithms such as ```std::copy```:
  
  - ```circ_begin(maxNumOfCirculations)```
  
    - circular iterator that equals ```circ_end()``` iterator when its number of ```circulations == maxNumOfCirculations```
  
  - ```circ_end()```
  
  - ```circ_cbegin(maxNumOfCirculations)```/```circ_cend()```
    
	- same as the above but for const access
  
  - ```circ_rbegin(maxNumOfCirculations)```

    - same as above but moves *backwards* in the buffer
  
  - ```circ_rend()```
  
  - ```circ_crbegin(maxNumOfCirculations)```/```circ_crend()```

    - same as above but for const access

- It defines a **Region Of Interest (ROI)** with its own ```roi_at``` and ```roi_circ_at``` access functions

- It defines all the equivalent **roi circular iterators** as the ones above, which can be used in **stl-like algorithms** to parse through the buffer's ROI

The blBuffer class defines also a single **circular write iterator** with corresponding **write** functions that are thread-safe and allow multiple parallel threads to write onto a common buffer

- The buffer offers a ```isBufferBeingCurrentlyWrittenTo()``` function which allows a user to ask whether the buffer is being currently written to

- The overloaded **write** functions allow the user to write data to the buffer from many types of input buffers, such as:

  - raw array

  - ```std::vector<T>```

  - raw pointers with a specified size
  
  - OpenCV's ```IplImage```, ```CvMat```, ```cv::Mat``` structures

- The ```write``` and corresponding ```write_no_wait``` functions do exactly that, they write data to the buffer, with the option to wait or quit without waiting in case another thread is currently writing to the buffer

- The **write iterator** is circular and will wrap around and continue writing, thus allowing threads to keep writing additional data to the buffer, where oldest data gets over-written with new data

The blBuffer class defines **read iterators** with corresponding ```read``` functions that allow a user to read data from the buffer into a specified external buffer

- every ```read``` function takes as its first input an **id**

  - The specified **id** uses the ```read<id>``` iterator
  
    - For example one thread could keep track of what it's read by using the ```read(0)``` function, while another thread would use ```read(1)``` function, another thread the ```read(-293)``` function and so on.

  - The blBuffer object instantiates a ```read<id>``` iterator if it doesn't have one yet, or uses the existing one if it already has one

## Why would I want to use this?

There could be many reasons where this blBuffer class would come in handy:

- For example, it can be seen as a 2D-buffer to represent images or 2D matrices, which can be used interchangibly with opencv's "IplImage", "CvMat" and "cv::Mat" structures in opencv's algorithms

  - It can be seen as a 3D-buffer to represent video streams, or 3D matrices

  - It can be seen as a 3D-buffer to represent Laplacian Pyramids or Gaussian Pyramids

  - It can be seen as a 4D-buffer to represent streams of Laplacian Pyramids or Gaussian Pyramids of videos or webcam feeds

  - It can be seen as a generic N-Dimensional contiguous buffer to represent custom data for advanced analisys algorithm and more

The main idea is that the data is contiguous, but is interpreted as an N-Dimensional space, so for example if you define a (3 x 4 x 6 x 10) buffer, the contiguous data will be seen as:

- 10 different slices of (3 x 4 x 6) data points

  - of which each slice is 6 pages of (3 x 4) data points

  - of which each page is 4 columns of (3) data points

  - of which each row is a single data point

## How do I use it?

The library is a header only template library that you can use by just including its header as follows:

```c++
#include <blBufferLIB.hpp>

// Everything is defined within the namespace: "blBufferLIB"

// More Examples coming soon...
```

## Under current development

The blBufferLIB is under current development, and the interface may change as I introduce more concepts to it


## Dependencies

* Mostly c++11 and some c++17 things like template folding

## License?

MIT License

Do what you like with the source, use it however you like, maybe even as a reference or learning material