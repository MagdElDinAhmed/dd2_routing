### README: Lee Maze Visualization Project

---

#### **Project Description**
This project visualizes the Lee Algorithm for maze routing, specifically applied to connecting pins on a grid-based layout. The project uses Python's `matplotlib` library to display a graphical representation of the grid, including obstacles, pins, and the paths calculated for each net.

---

#### **Technical Overview**
1. **Input Files**:
   - **`input.txt`**:
     - Contains the grid dimensions, obstructions, and net pins to be connected.
     - Example:
       ```
       300, 200, 20, 5
       OBS (1, 33, 44)
       OBS (2, 55, 77)
       net1 (1, 10, 20) (2, 30, 50) (1, 5, 100)
       net2 (2, 100, 200) (1, 300, 50)
       net3 (1, 100, 50) (2, 300, 150) (2, 50, 50) (1, 2, 2)
       ```
   - **`output.txt`**:
     - Contains the calculated paths for each net.
     - Example:
       ```
       net1 (1,10,20) (1,10,21) ... (2,30,50)
       net2 (2,100,200) (2,101,200) ... (1,300,50)
       net3 (1,100,50) (1,100,51) ... (1,300,150)
       ```

2. **Visualization Components**:
   - **Grid**:
     - Represented as a rectangular boundary.
     - Only the outer border of the grid is displayed to keep the visualization clean.
   - **Obstructions**:
     - Shown as **black cells** on the grid, indicating areas that cannot be used.
   - **Pins**:
     - Represented by **red cells** where each net begins or ends.
   - **Paths**:
     - Calculated by the Lee Algorithm and visualized using distinct colors for each net.
     - Example Colors:
       - `net1`: Blue
       - `net2`: Green
       - `net3`: Orange

3. **Visualization Details**:
   - **`matplotlib`**:
     - Used for static visualization of the grid and paths.
   - **Dynamic Coloring**:
     - Paths are color-coded to differentiate between nets.
   - **Aspect Ratio**:
     - The grid is displayed with an equal aspect ratio to ensure cells appear square.
   - **Annotations**:
     - The visualization is divided into two grids:
       - **Metal Layer 1**: For paths and obstacles on layer 1.
       - **Metal Layer 2**: For paths and obstacles on layer 2.

4. **Algorithm**:
   - The Lee Algorithm is used to calculate the shortest path connecting the pins of each net.
   - The paths account for:
     - Grid constraints (dimensions and obstacles).
     - Layer transitions for multi-layer paths.

---

#### **How to Use**
1. **Input Files**:
   - Place `input.txt` and `output.txt` in the project directory.
   - Ensure the input format matches the expected structure.

2. **Run the Script**:
   - Execute the Python script:
     ```
     python lee_maze_visualization.py
     ```

3. **Output**:
   - A graphical visualization of the grid with obstacles, pins, and calculated paths.

---

#### **Key Features**
- **Clean Visualization**:
  - No grid lines, only the outer border is displayed for clarity.
- **Dynamic Path Colors**:
  - Each net's path is displayed in a distinct color for better differentiation.
- **Multi-Layer Support**:
  - Obstructions, pins, and paths are visualized separately for each metal layer.

---

#### **Dependencies**
- Python 3.x
- `matplotlib`

To install dependencies, run:
```bash
pip install matplotlib
```

---

#### **Future Enhancements**
- Add interactivity to explore specific paths and nets.
- Support for dynamic input through a GUI or web interface.
- Integration with a backend Lee Algorithm implementation for real-time pathfinding.

---

Feel free to contribute or raise issues for enhancements! 😊
