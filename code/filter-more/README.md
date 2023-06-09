# filter-more, week 5
This exercise's the goal is to manage functions declared at "helpers.c" file to handle with image pixels applying filters to them;

The grayscale function was pretty clean (and easy) to implement once it's logic is simple, just taking each pixel value and set all of them to the average of all (red, green and blue);

At reflect function I decided to implement a logic that splits the image into 2 pieces flipping each pixel with it's counterpart having it's "highlight" (the point I really liked) at j index math { image[i][width-j-1] }, decreasing the pixel according with j increase, featuring some thinking process images taken at paint;

At the blur function I learn a very interesting logic using 4 loops to validates the math using the pixels;
it's first version was a lotta "brute force thought" once it's first version was made with a whole bunch of if's (the other.c file illustrates what I mean), applying the 4 loops logic after I discover it at the edges function;

The last and hardest function was edges, where I must implement a function that average the whole 3x3 pixels average of all RGB values using a specific kernel and assign it to the middle, the principal pixel;
The catch in edges and blur functions is that is needed to create a copy of the entire RGB array to don't interfer at the results, and assign it ot the original array only at the final;
the logic is clean and leaned the 4 loops logic to validate a 3x3 matrix with a given logic;