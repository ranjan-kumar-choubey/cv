
# Purpose: To find the optimal solution, given 2-D objective func along with constraints, by Brute-Force
# Written by: P Sai Srujan
# Written on: 11-12-2023

'''
Maximize Z = 5x + 4y
    6x + 4y <= 24
    x + 2y <= 6
    -x + y <= 1
    y <= 2
    x >= 0
    y >= 0

5 4 0
    6 4 24 0
    1 2 6 0
    -1 1 1 0
    0 1 2 0
    1 0 0 1
    0 1 0 1

Minimize Z = 3.3x + 0.9y
    x + y >= 800
    0.21x + -0.3y <= 0
    0.03x + -0.01y >= 0
    x >= 0
    y >= 0

0.3 0.9 1
    1 1 800 1
    0.21 -0.3 0 0
    0.03 -0.01 0 1
    1 0 0 1
    0 1 0 1

Maximize Z = 3x + 2y
    2x + y <= 100
    x + y <= 80
    x <= 40
    x >= 0
    y >= 0

3 2 0
    2 1 100 0
    1 1 80 0
    1 0 40 0
    1 0 0 1
    0 1 0 1

Maximize Z = 5x + 10y
    x + 2y <= 120
    x + y >= 60
    x - 2y >= 0
    x >= 0
    y >= 0

5 10 0
    1 2 120 0
    1 1 60 1
    1 -2 0 1
    1 0 0 1
    0 1 0 1
'''

import numpy as np
import matplotlib.pyplot as plt

def plot_line(a, b, c, fpoints, lines):
    if b!=0:
        x_values = np.array(plt.xlim())
        # Calculate corresponding y values using the equation ax + by = c
        y_values = (c - a * x_values) / b
    elif a!=0:
        y_values = np.array(plt.ylim())
        x_values = (c - b * y_values) / a

    points = np.column_stack((x_values, y_values))    
    for point in points:
        if point_satisfies_constraints(point, lines):
            fpoints.append(point)
    plt.plot(x_values, y_values, color='blue')

    return fpoints

def find_intersection_points(lines):
    num_lines = len(lines)
    intersection_points = []
    for i in range(num_lines):
        for j in range(i + 1, num_lines):
            line1 = lines[i]
            line2 = lines[j]
            
            a1, b1, c1 = line1
            # plot_line(a1, b1, c1)
            a2, b2, c2 = line2
            # plot_line(a2, b2, c2)
            
            # Solve the system of equations for x and y
            determinant = a1 * b2 - a2 * b1
            if determinant != 0:
                x = (c1 * b2 - c2 * b1) / determinant
                y = (a1 * c2 - a2 * c1) / determinant
                
                intersection_points.append((x, y))
    
    return intersection_points

obj=None
# Function to read equations from a file
def read_equations_from_file(file_path):
    lines = []
    lno=0;global obj
    with open(file_path, 'r') as file:
        for line in file:
            if lno==0:
                a, b, m = map(float, line.strip().split())
                obj= (a, b, m)
                lno=1
            else:
                # Split the line into coefficients
                a, b, c, d = map(float, line.strip().split())
                if(d==0):   # (0 : <=), (1 : >=)
                    lines.append((a, b, c))
                else:
                    lines.append((-a, -b, -c))
    return lines

def point_satisfies_constraints(point, constraints):
    x, y = point
    for a, b, c in constraints:
        if a * x + b * y > c:
            return False  # Point violates at least one constraint   
    return True  # Point satisfies all constraints

def find_optimal_point(points):
    if not points:
        return None
    
    global obj
    a, b, m = obj[0], obj[1], obj[2]
    if m==0:            # m=0 : Maximise, m=1 :minimise
        a, b = -a, -b

    optimal_point = points[0]
    min_value = a * points[0][0] + b * points[0][1]
    
    for point in points:
        value = a * point[0] + b * point[1]
        if value < min_value:
            min_value = value
            optimal_point = point
    
    if m==0:
        min_value=-min_value
    return optimal_point, min_value

def orientation(p, q, r):
    val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1])
    if val == 0:
        return 0  # Collinear
    return 1 if val > 0 else 2  # Clockwise or counterclockwise

def convex_hull(points):
    n = len(points)
    if n < 3:
        return []

    hull = []

    # Find the leftmost point
    leftmost = 0
    for i in range(1, n):
        if points[i][0] < points[leftmost][0]:
            leftmost = i

    p = leftmost
    while True:
        hull.append(points[p])

        q = (p + 1) % n
        for i in range(n):
            if orientation(points[p], points[i], points[q]) == 2:
                q = i

        p = q

        if p == leftmost:
            break

    return hull

def plot_convex_hull(points):
    # Compute the convex hull
    hull_points = convex_hull(points)
    # Add the first point to close the loop
    hull_points.append(hull_points[0])
    # Extract x and y coordinates for plotting
    x_coords, y_coords = zip(*hull_points)    
    # Shade the region inside the polygon
    plt.fill(x_coords, y_coords, color='green', alpha=0.5)
    

file_path = 'equations.txt'
lines = read_equations_from_file(file_path)
intersection_points = find_intersection_points(lines)
x_coordinates, y_coordinates = zip(*intersection_points)
plt.scatter(x_coordinates, y_coordinates, color='black', label='Intersection_Points', marker='o')

feasible_points=[]
for point in intersection_points:
    if point_satisfies_constraints(point, lines):
        feasible_points.append(point)

x_coordinates, y_coordinates = zip(*feasible_points)
# plt.plot(x_coordinates, y_coordinates, color='lightcoral', label='Feasible_Points')
plt.scatter(x_coordinates, y_coordinates, color='red', label='Feasible_Points', marker='o')

opt_pt, opt_val = find_optimal_point(feasible_points)

optimal_point=[]
optimal_point.append((round(opt_pt[0],2), round(opt_pt[1],2)))
x_coordinates, y_coordinates = zip(*optimal_point)
plt.scatter(x_coordinates, y_coordinates, color='green', label='Optimal_Point', marker='o')
print(optimal_point[0],round(opt_val,2))


plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.title("Corner Points Plot")

for line in lines:
    a1, b1, c1 = line
    feasible_points = plot_line(a1, b1, c1, feasible_points, lines)

print(feasible_points)
plot_convex_hull(feasible_points)

# Show the plot
plt.legend()
plt.grid()
plt.show()