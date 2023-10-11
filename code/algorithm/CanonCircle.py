
# Purpose: To print distinct canonical circles for all the subsets, given Set of 2-D points
# Written by: P Sai Srujan
# Written on: 04-10-2023

from itertools import combinations
import math

def generate_subsets(points):
    all_subsets = []
    for r in range(len(points) + 1):
        subsets = combinations(points, r)
        all_subsets.extend(subsets)
    
    return all_subsets

def generate_subsets_of_size_3(points):
    subsets = list(combinations(points, 3))
    return subsets

def calculate_distance(point1, point2):
    x1, y1 = point1
    x2, y2 = point2
    return math.sqrt((x2 - x1)**2 + (y2 - y1)**2)

def find_two_farthest_points(points):

    max_distance = 0
    farthest_point1 = None
    farthest_point2 = None
    
    for i in range(len(points)):
        for j in range(i + 1, len(points)):
            distance = calculate_distance(points[i], points[j])
            if distance > max_distance:
                max_distance = distance
                farthest_point1 = points[i]
                farthest_point2 = points[j]
    
    return farthest_point1, farthest_point2

def find_circle_radius_and_center(point1, point2):
    # Calculate the coordinates of the midpoint
    center_x = (point1[0] + point2[0]) / 2
    center_y = (point1[1] + point2[1]) / 2
    center=(center_x,center_y)

    # Calculate the radius using the distance formula
    radius = calculate_distance(point1,center)
    
    return radius, (center_x, center_y)
    
    return all_subsets

def distances_to_point(given_point, points):
    distances = []
    for point in points:
        distance = calculate_distance(given_point, point)
        distances.append((point, distance))
    return distances

def find_circle_3points(point1, point2, point3):
    x1, y1 = point1
    x2, y2 = point2
    x3, y3 = point3
    
    # Calculate the midpoints of two sides of the triangle
    midpoint1 = ((x1 + x2) / 2, (y1 + y2) / 2)
    midpoint2 = ((x2 + x3) / 2, (y2 + y3) / 2)
    
    # Calculate the slopes of the lines passing through these midpoints
    if x2 - x1 != 0:
        slope1 = (y2 - y1) / (x2 - x1)
    else:
        slope1 = math.inf  # Vertical line
    if x3 - x2 != 0:
        slope2 = (y3 - y2) / (x3 - x2)
    else:
        slope2 = math.inf  # Vertical line
    
    # Calculate the center of the circle (circumcenter)
    if slope1 == slope2:
        return None, None  # Points are collinear, no unique circumcenter
    
    center_x = (slope1 * midpoint1[0] - slope2 * midpoint2[0] + midpoint2[1] - midpoint1[1]) / (slope1 - slope2)
    center_y = midpoint1[1] - slope1 * (center_x - midpoint1[0])
    
    # Calculate the radius of the circle (circumradius)
    radius = math.sqrt((center_x - x1)**2 + (center_y - y1)**2)
    
    return radius, (center_x, center_y)



points = [(1,0), (2,0), (3,0), (4,0), (5,0)]
points = [(1,1), (3,1), (1,3)]
all_subsets = generate_subsets(points)

circleSet=set()
for subset in all_subsets:
    # print(subset)
    if(len(subset)==1):
        circleSet.add((0.0,subset[0]))
    elif(len(subset)==2):
        r,c=find_circle_radius_and_center(subset[0],subset[1])
        circleSet.add((round(r,3),c))
    elif(len(subset)==3):
        r,c=find_circle_3points(subset[0],subset[1], subset[2])
        if r is not None:
            circleSet.add((round(r,3),c))
    else:
        subsets1=generate_subsets_of_size_3(subset)
        valid=True
        for subset1 in subsets1:
            r,c=find_circle_3points(subset1[0],subset1[1], subset1[2])
            if r is not None:
                test=[x for x in subset if x not in subset1]
                distances=distances_to_point(c,test)
                for point, distance in distances:
                    if distance>r:
                        valid=False
                        break
                if valid==True:
                    circleSet.add((round(r,3),c))
print(circleSet)
print(len(circleSet))