# dd2_routing
An implementation of Lee's maze algorithm in C++

## Implementation
We utilized a 3D vector where the 1st dimension references the metal layer, the 2nd references the y value, and the 3rd references the x value.
## Compilation
### Classes
#### CellType
It is an enum indicating if a cell is:
- Empty
- Obstacle
- Pin
- Wire
- Source
- Target

The last 2 are used specifically during the routing stage and are converted to pins and wires afterwards
#### Cell
It contains a cost and its cell type. It's functions are setters and getters. This is used to identify occupancy and cost during the routing process and cost is initialized to `INT32_MAX` and reset to `INT32_MAX` after each net route.
#### Net
It contains a net id and a vector containing the coordinates of the various pins in that net. Its functions are setters and getters. Additionally, you can add pins individually to the net and display all pins in the net.
#### TextParser
It only contains the file name of the file it opens as a property. Instead its job primarily revolves around text parsing mentioned later in execution.
## Execution
### Input Parsing
First, we needed to have our input values ready before we can begin routing in order to know the size of the grid, the penalties, and the location of obstacles and pins. What we began doing was reading the first line and extract the numbers and assign them to the correct variables. Then we go through the file line by line identifying obstacles and nets then extracting the coordinates of the obstacles and pins.

During the process, we need to ensure data validity, so we check that:
- The data is numbers
- There are 3 numbers for the coordinates
- The numbers are positive
- All coordinates are within the boundaries
- No obstacle or pin is being placed in an occupied space

For the first line specifically, we check that we only have 4 numbers.
## Team Workflow
Work was initially split as global routing, detailed routing, and visualization. Global routing was dropped due to complexities regarding sizing the global boxes and making the dynamic costs make sense. Eventually, the initial setup and parsing proved to be sufficient work instead of global routing. Parsing had to be done first, but visualization van run in parallel given a mock routed path.
## Individual Contributions
### MagdElDin AbdalRaaof
#### Contributions
- Provided text parsing
- Wrote the initial code for the classes used
- Initial set up of the nets, obstacles, and the grid itself
#### Challenges
- Ensuring errors in the text file are accounted for such that the program doesn't crash or produce errors
### Tarek Kassab

### Yousef Mansour
