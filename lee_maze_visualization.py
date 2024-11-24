import matplotlib.pyplot as plt

# function to read a file
def read_file(file_path):
    with open(file_path, "r") as file:
        return file.read()
        
# function to parse the input data
def parse_input(input_data):
    lines = input_data.strip().split("\n")
    grid_info = list(map(int, lines[0].split(", ")))
    grid_width, grid_height, bend_penalty, via_penalty = grid_info

    obstructions = {} # coordinates: color
    nets = {} # name: coordinates. The colors are in a different dictionaries indexed by name

    # parse obstructions and nets
    for line in lines[1:]:
        line = line.strip()
        if line.startswith("OBS"):
            layer, x, y = map(int, line[line.index("(") + 1:line.index(")")].split(","))
            obstructions[(layer, x, y)] = "black"
        elif line.startswith("net"):
            parts = line.split(" ", 1)  # split into net name and rest of the line
            net_name = parts[0]
            pin_coords = parts[1].split(") (")  # split each pin by ") ("
            pins = [tuple(map(int, coord.replace("(", "").replace(")", "").split(","))) for coord in pin_coords]
            nets[net_name] = pins
    return grid_width, grid_height, obstructions, nets
    
 
# function to parse the output paths/routes data
def parse_paths(output_data):
    paths = {}
    lines = output_data.strip().split("\n")
    for line in lines:
        parts = line.split(" ", 1)
        net_name = parts[0]
        path_coords = parts[1].split(") (")
        path = [tuple(map(int, coord.replace("(", "").replace(")", "").split(","))) for coord in path_coords]
        paths[net_name] = path
    return paths
    
    
# function to draw the grid
def draw_detailed_grid(ax, grid_width, grid_height, layer, obstructions, nets, paths, title, colors):
    # Draw outer border of the grid
    ax.plot([0, grid_width, grid_width, 0, 0], [0, 0, grid_height, grid_height, 0], 'k-', lw=0.3)
    
    # mark obstructions
    for (obs_layer, x, y), color in obstructions.items():
        if obs_layer == layer:
            ax.add_patch(plt.Rectangle((x - 1, y - 1), 1, 1, color=color))
    
    # mark nets
    for net, pins in nets.items():
        net_color = colors[net]
        for pin_layer, x, y in pins:
            if pin_layer == layer:
                ax.add_patch(plt.Rectangle((x - 1, y - 1), 1, 1, color=net_color))
    
    # mark paths with distinct colors
    for net_name, path in paths.items():
        path_color = colors[net_name]
        for point_layer, x, y in path:
            if point_layer == layer:
                ax.add_patch(plt.Rectangle((x - 1, y - 1), 1, 1, color=path_color))
    
    # Adjust settings
    ax.set_xlim(0, grid_width)
    ax.set_ylim(0, grid_height)
    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_aspect('equal')
    ax.set_title(title, fontsize=10, pad=10)
    
    
input_file = "input.txt"
output_file = "output.txt"

input_data = read_file(input_file)
output_data = read_file(output_file)

# parse the input and output data
grid_width, grid_height, obstructions, nets = parse_input(input_data)
paths = parse_paths(output_data)

colors = {
    "net1": "purple",
    "net2": "green",
    "net3": "orange"
}

fig, axs = plt.subplots(1, 2, figsize=(18, 9))

draw_detailed_grid(axs[0], grid_width, grid_height, 1, obstructions, nets, paths, "Metal Layer 1", colors)
draw_detailed_grid(axs[1], grid_width, grid_height, 2, obstructions, nets, paths, "Metal Layer 2", colors)

plt.tight_layout()
plt.show()
