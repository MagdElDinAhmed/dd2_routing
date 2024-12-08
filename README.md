# dd2_routing
An implementation of Lee's maze algorithm in C++

## Implementation
We utilized a 3D vector where the 1st dimension references the metal layer, the 2nd references the y value, and the 3rd references the x value.
We mark all the pins as Targets, then loop over each of them checking if they are a Source or not. If not we mark them as a source and connect them to
the nearest Target using an algorithm based of Dijkstra's algorithm. We trace back from the target to source marking the road as source wires as well.
We repeat this process for each net printing the results of each net after we are done with it and marking all the used pins and wires in the connection
as obstacles for future nets.
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
It contains a cost and its cell type. It's functions are setters and getters. This is used to identify occupancy and cost during the routing process and cost is initialized to `INT_MAX` and reset to `INT_MAX` after each net route.
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
# How to run
## Linux Operating System

Follow these steps to set up, build, and run the project on Ubuntu:

### Prerequisites

Ensure you have the required tools installed. Run:
```bash
sudo apt install cmake build-essential
```

### Steps to Build and Run

1. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   ```
   Replace `<repository-url>` with the actual URL of the repository.

2. **Create a Build Directory**:
   ```bash
   mkdir build
   cd build
   ```

3. **Generate Build Files with CMake**:
   ```bash
   cmake ..
   ```

4. **Build the Project**:
   ```bash
   make
   ```

5. **Run the Executable**:
   ```bash
   ./DD2-Maze-Router
   ```
---

## Windows Operating System
- make the project
- Place the input file in the exe folder then build and run `DD2-Maze-Router.cpp` and type the name of the input file when prompted.

# Grid Visualization Tool

This script ```lee_maze_visualization.py``` visualizes routing grids for EDA tasks, including obstructions, nets, and routed paths. It dynamically colors nets and supports multiple layers with distinct visual styles.

### Features

- Parses **input** (grid, obstructions, nets) and **output** (paths) files.
- Displays grid with **obstructions**, **net pins**, **routed paths**, and **vias**.
- Assigns random **unique colors** to nets with a legend.

### Requirements

- **Python 3.6+**
- **matplotlib**

### Input File Format

1. **Grid Information**: `<grid_width>, <grid_height>, <bend_penalty>, <via_penalty>`
2. **Obstructions**: `OBS (<layer>, <x>, <y>)`
3. **Nets**: `<net_name> (<layer>, <x>, <y>) (<layer>, <x>, <y>)`

#### Example
```
25, 50, 3, 5
OBS (0, 15, 27)
net1 (0, 10, 30) (0, 20, 30)
```

### Output File Format

Each net’s path:
```
<net_name> (<layer>, <x>, <y>) (<layer>, <x>, <y>) ...
```

#### Example
```
net1 (1,20,30) (1,19,30)
```

### How to Use

1. Set file paths (e.g.):
   ```python
   input_file = "Test Sets/Test_6/input.txt"
   output_file = "Test Sets/Test_6/output.txt"
   ```
2. Run the script:
   ```bash
   python lee_maze_visualization.py
   ```
3. View the generated plots:
   - **Figure 1**: Routed paths.
   - **Figure 2**: Individual pins at the beginning.

### Customization

- Modify colors in `random_color()`.
- Adjust grid styles in `draw_merged_grid()`.

### Example Outputs

- **Input**: Nets, obstructions, and paths parsed from files.
- **Visualization**: Color-coded grid with paths, pins, and vias.

---

**Note**: Ensure correct input/output file formats for accurate results.

---

### **Tests**
test 1:

- 25x25 grid
- No additional penalties for using vias or going against the preferred path
- No obstacles
- 3 nets, each having 2 pins, and all pins are on layer 0

test 2:

- 25x25 grid
- No additional penalties for using vias or going against the preferred path
- Obstacles are present on the direct path between the pins
- 3 nets, each having 2 pins, and the 2 pins are either on the same x value or the same y value
- 1 of the nets has both pins on the same layer
- 2 nets have the pins on different layers

test 3:

- 25x50 grid
- Penalty for using a via is 5
- Penalty for going against the preferred path is 3
- Obstacles are present. Some are expensive enough to make using a via more effective for one net. Others make the router choose to go against the preferred path for another.
- 2 nets, each having 2 pins, and the pins of each net are on the same metal layer

test 4:

- 25x50 grid
- Penalty for using a via is 3
- Penalty for going against the preferred path is 5
- Obstacles are present. Some are expensive enough to make using a via more effective for one net. Others make the router choose to go against the preferred path for another.
- 2 nets, each having 2 pins, and the pins of each net are on the same metal layer

test 5:

- 25x50 grid
- Penalty for using a via is 5
- Penalty for going against the preferred path is 3
- No obstacles. The wires of one net will become the obstacles for another
- 2 nets, each having 2 pins, and the pins are on the same metal layer

test 6:

- 50x25 grid
- No additional penalties for using vias or going against the preferred path
- No obstacles
- 1 net with 4 pins, 2 of the pins are on one layer and the other 2 are on the other

test 7:

- 25x25 grid
- Penalty for using a via is 10
- Penalty for going against the preferred path is 4
- Obstacles completely surround a pin
- 1 net with 2 pins on the same layer

test 8:
- 50x50 grid
- Penalty for using a via is 20
- Penalty for going against the preferred path is 10
- No obstacles
- 1 net having 3 pins, and the pins are on the same layer with a fork in the road

(BONUS)
test 9:

- 25x25 grid
- Penalty for using a via is 10
- Penalty for going against the preferred path is 4
- No obstacles.
- Have net1 have 6 pins, net2 have 5 pins, net3 have 4 pins, net4 have 3 pins, net5 have 2 pins to test ordering (all pins on the same layer)

test 10:

- 25x25 grid
- Penalty for using a via is 10
- Penalty for going against the preferred path is 4
- No obstacles.
- 5 nets with 3 pins each to test ordering on equal pin counts

test 11:

- 25x25 grid
- Penalty for using a via is 10
- Penalty for going against the preferred path is 4
- No obstacles.
- Have net1 have 6 pins, net2 have 5 pins, net3 have 4 pins, net4 have 3 pins, net5 have 2 pins to test ordering (have pins on different layers)

---
## Team Workflow
Work was initially split as global routing, detailed routing, and visualization. Global routing was dropped due to complexities regarding sizing the global boxes and making the dynamic costs make sense. Eventually, the initial setup and parsing proved to be sufficient work instead of global routing. Parsing had to be done first, but visualization van run in parallel given a mock routed path.
## Individual Contributions
### MagdElDin AbdalRaaof
#### Contributions
- Provided text parsing
- Wrote the initial code for the classes used
- Initial set up of the nets, obstacles, and the grid itself
- Aided in the routing algorithm development
- Aided in visualization development
- Developed the test cases
- Worked on Net Ordering Heuristic
#### Challenges
- Ensuring errors in the text file are accounted for such that the program doesn't crash or produce errors
### Tarek Kassab
- Implemented the routing algorithm based off data provided by Magd's Code
### Yousef Mansour
- Visulaization
