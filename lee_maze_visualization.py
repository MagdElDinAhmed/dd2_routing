import random
import colorsys

import matplotlib.pyplot as plt
import matplotlib.patches as patches

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
            obstructions[(layer, x, y)] = "gray"
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
# function to draw the grid
def draw_merged_grid(ax, grid_width, grid_height, obstructions, nets, paths, title, colors):
    # Draw outer border of the grid with adjusted origin
    ax.plot([-1, grid_width, grid_width, -1, -1], [-1, -1, grid_height, grid_height, -1], 'k-', lw=0.3)

    # Mark obstructions
    for (layer, x, y), color in obstructions.items():
        if layer == 2:
            # Second layer obstructions: black with white circular patterns
            ax.add_patch(plt.Rectangle((x, y), 1, 1, facecolor='black', hatch='o', edgecolor='black', linewidth=0.3))
        else:
            # Default style for other layers
            ax.add_patch(plt.Rectangle((x, y), 1, 1, facecolor=color))

    # Mark nets
    for net, pins in nets.items():
        net_color = colors[net]
        for layer, x, y in pins:
            hatch = 'x' if layer == 1 else 'o'
            ax.add_patch(plt.Rectangle((x, y), 1, 1, color=net_color, hatch=hatch))

    # Mark paths with distinct colors and layer-specific opacity
    for net_name, path in paths.items():
        path_color = colors[net_name]
        for layer, x, y in path:
            # Make layer 1 more transparent than layer 2
            opacity = 0.4 if layer == 1 else 0.8
            hatch = 'x' if layer == 1 else 'o'
            ax.add_patch(plt.Rectangle((x, y), 1, 1,
                                     facecolor=path_color,
                                     alpha=opacity,
                                     hatch=hatch))

    # Mark vias
    for net_name, path in paths.items():
        for i in range(1, len(path)):
            if path[i][0] != path[i-1][0]:  # Different layers
                x, y = path[i][1], path[i][2]
                ax.add_patch(patches.Circle((x + 0.5, y + 0.5), 0.2, color='red'))

    # Add grid lines, including the extended range
    ax.set_xticks(range(-1, grid_width + 1))
    ax.set_yticks(range(-1, grid_height + 1))
    ax.grid(which='both', color='grey', linestyle='-', linewidth=0.5)

    # Adjust settings for the shifted grid
    ax.set_xlim(-1, grid_width)
    ax.set_ylim(-1, grid_height)
    ax.set_aspect('equal')
    ax.set_title(title, fontsize=10, pad=10)



input_file = "Test Sets/Test_6/input.txt"
output_file = "Test Sets/Test_6/output.txt"

input_data = read_file(input_file)
output_data = read_file(output_file)

# parse the input and output data
grid_width, grid_height, obstructions, nets = parse_input(input_data)
paths = parse_paths(output_data)

# Generate a random color
def random_color():
    h, s, l = random.random(), 0.5 + random.random() / 2, 0.4 + random.random() / 5
    r, g, b = [int(256 * i) for i in colorsys.hls_to_rgb(h, l, s)]
    return "#{:02x}{:02x}{:02x}".format(r, g, b)

# Assign a unique color to each net dynamically
colors = {net: random_color() for net in nets}
# Create a legend for the nets
legend_patches = [patches.Patch(color=color, label=net) for net, color in colors.items()]


# First figure
fig1, ax1 = plt.subplots(figsize=(9, 9))
ax1.legend(handles=legend_patches, loc='upper right', fontsize='small', title='Nets')
draw_merged_grid(ax1, grid_width, grid_height, obstructions, nets, paths, "Merged Metal Layers", colors)
plt.tight_layout()
# Second figure
paths_pins = {
    key: [(t[0] + 1, t[1], t[2]) for t in value]
    for key, value in nets.items()
}
fig2, ax2 = plt.subplots(figsize=(9, 9))
ax2.legend(handles=legend_patches, loc='upper right', fontsize='small', title='Nets')
draw_merged_grid(ax2, grid_width, grid_height, obstructions, nets, paths_pins, "Merged Metal Layers", colors)
plt.tight_layout()

# Show all figures at once
plt.show()
