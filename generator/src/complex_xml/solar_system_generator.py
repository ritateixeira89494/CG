from random import random, randint
import xml.etree.cElementTree as Tree
from numpy import pi,sin,cos
from sys import argv

def define_camera(world):
    camera = Tree.SubElement(world, 'camera')
    position = Tree.SubElement(camera, 'position')
    position.attrib['x'] = '52'
    position.attrib['y'] = '70'
    position.attrib['z'] = '164'

    lookat = Tree.SubElement(camera, 'lookAt')
    lookat.attrib['x'] = '0'
    lookat.attrib['y'] = '0'
    lookat.attrib['z'] = '0'

    up = Tree.SubElement(camera, 'up')
    up.attrib['x'] = '0'
    up.attrib['y'] = '1'
    up.attrib['z'] = '0'
    
    projection = Tree.SubElement(camera, 'projection')
    projection.attrib['fov'] = '60'
    projection.attrib['near'] = '1'
    projection.attrib['far'] = '1000'


def draw_group(parent, models=None, transforms=None, comment=None):
    group = Tree.SubElement(parent, 'group')

    if comment is not None:
        com = Tree.Comment(comment)
        group.append(com)

    transforms_elem = Tree.SubElement(group, 'transform')
    for name, attribs, children in transforms:
        transform_elem = Tree.SubElement(transforms_elem, name)

        for id, value in attribs:
            transform_elem.attrib[id] = value

        if children:
            for child_name, child_attribs in children:
                child_elem = Tree.SubElement(transform_elem, child_name)
                for child_id, child_value in child_attribs:
                    child_elem.attrib[child_id] = child_value

    models_elem = Tree.SubElement(group, 'models')
    for model in models:
        model_elem = Tree.SubElement(models_elem, 'model')
        model_elem.attrib['file'] = model

    return group


def get_ctrl_points_circle(radius, num=16):
    points = []
    for i in range(num):
        angle = -((i / num) * 2*pi)
        x = cos(angle) * radius
        y = 0
        z = sin(angle) * radius

        points.append(('point', [('x', str(x)), ('y', str(y)), ('z', str(z))]))

    return points


def get_ctrl_points_ellipse(a_radius, b_radius, num=16):
    points = []
    for i in range(num):
        angle = -((i/num) * 2*pi) # Here we are flipping
        x = cos(angle) * a_radius
        y = 0
        z = sin(angle) * b_radius

        points.append(('point', [('x', str(x)), ('y', str(y)), ('z', str(z))]))

    return points


def get_ctrl_points_line(length, num=4):
    points = []
    for i in range(num):
        x = -(i*length / num)
        y = 0
        z = 0

        points.append(('point', [('x', str(x)), ('y', str(y)), ('z', str(z))]))

    return points


def draw_sun(parent):
    models = [sphere]
    comment = 'Sun'
    
    transforms = [ 
        ('scale', [('x','15'),('y','15'),('z','15')], None),
        ('rotate', [('time','60'),('x','0'),('y','1'),('z','0')], None)
     ]

    return draw_group(parent, models, transforms, comment)

def draw_mercury(parent):
    radius = 25
    models = [sphere]
    comment = 'Mercury'
    points = get_ctrl_points_circle(radius)
    transforms = [ 
        ('translate', [('time', '15'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '10'), ('x', '0'), ('y','1'), ('z','0')], None),
        ('scale', [('x','0.49'),('y','0.49'),('z','0.49')], None),
    ]

    return draw_group(parent, models, transforms, comment)


def draw_venus(parent):
    radius = 30
    models = [sphere]
    comment = 'Venus'
    points = get_ctrl_points_circle(radius)
    transforms = [
        ('translate', [('time', '20'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '15'), ('x', '0'), ('y','-1'), ('z','0')], None),
        ('scale', [('x','1.21'),('y','1.21'),('z','1.21')], None)
    ]

    return draw_group(parent, models, transforms, comment)


def draw_earth(parent):
    radius = 35
    models = [sphere]
    comment = 'Earth'
    points = get_ctrl_points_circle(radius)
    transforms = [ 
        ('translate', [('time', '25'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '13'), ('x', '0'), ('y','1'), ('z','0')], None),
        ('scale', [('x','1.27'),('y','1.27'),('z','1.27')], None),
    ]

    earth = draw_group(parent, models, transforms, comment)
    draw_moon(earth)

    return earth


def draw_moon(parent):
    radius = 5
    models = [sphere]
    comment = 'Moon'
    points = get_ctrl_points_circle(radius)
    transforms = [ 
        ('translate', [('time', '10'), ('align', 'True'), ('draw', 'True')], points),
        ('scale', [('x','0.35'),('y','0.35'),('z','0.35')], None),
    ]

    return draw_group(parent, models, transforms, comment)
    

def draw_mars(parent):
    radius = 45
    models = [sphere]
    comment = 'Mars'
    points = get_ctrl_points_circle(radius)
    transforms = [ 
        ('translate', [('time', '35'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '10'), ('x', '0'), ('y','1'), ('z','0')], None),
        ('scale', [('x','0.68'),('y','0.68'),('z','0.68')], None),
    ]

    return draw_group(parent, models, transforms, comment)


def draw_jupiter(parent):
    radius = 55
    models = [sphere]
    comment = 'Jupiter'
    points = get_ctrl_points_circle(radius)
    transforms = [ 
        ('translate', [('time', '45'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '30'), ('x', '0'), ('y','1'), ('z','0')], None),
        ('scale', [('x','5'),('y','5'),('z','5')], None),
    ]

    return draw_group(parent, models, transforms, comment)


def draw_saturn(parent):
    radius = 70
    models = [sphere]
    comment = 'Saturn'
    points = get_ctrl_points_circle(radius)
    transforms = [ 
        ('translate', [('time', '55'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '35'), ('x', '0'), ('y','1'), ('z','0')], None),
        ('scale', [('x','3.5'),('y','3.5'),('z','3.5')], None),
    ]
    asteroids = 1000

    saturn = draw_group(parent, models, transforms, comment)
    
    for i in range(asteroids):
        radius = random() + 2
        translate_time = randint(10, 40)
        rotation = randint(0, 360)
        draw_saturn_asteroid(saturn, radius, translate_time, rotation)

    return saturn


def draw_saturn_asteroid(parent, radius, translate_time, rotation):
    models = [sphere_very_low_detail]
    comment = 'Saturn Asteroid'
    points = get_ctrl_points_circle(radius)
    transforms = [ 
        ('rotate', [('time', '35'), ('x', '0'), ('y','-1'), ('z','0')], None), # Undo rotation applied to Saturn
        ('rotate', [('angle', str(rotation)), ('x', '0'), ('y','1'), ('z','0')], None),
        ('translate', [('time', str(translate_time)), ('align', 'False'), ('draw', 'False')], points),
        ('scale', [('x','0.01'),('y','0.01'),('z','0.01')], None),
    ]

    return draw_group(parent, models, transforms, comment)


def draw_uranus(parent):
    radius = 85
    models = [sphere]
    comment = 'Uranus'
    points = get_ctrl_points_circle(radius)
    transforms = [ 
        ('translate', [('time', '65'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '40'), ('x', '0'), ('y','-1'), ('z','0')], None),
        ('scale', [('x','2.57'),('y','2.57'),('z','2.57')], None),
    ]

    return draw_group(parent, models, transforms, comment)


def draw_neptune(parent):
    radius = 95
    models = [sphere]
    comment = 'Neptune'
    points = get_ctrl_points_circle(radius)
    transforms = [ 
        ('translate', [('time', '75'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '45'), ('x', '0'), ('y','1'), ('z','0')], None),
        ('scale', [('x','2.27'),('y','2.27'),('z','2.27')], None),
    ]

    return draw_group(parent, models, transforms, comment)


def draw_commet_trail(parent):
    length = 40
    models = [sphere_very_low_detail]
    comment = 'Commet Trail'
    trail_num = 1000

    for i in range(trail_num):
        angle_x = random()
        angle_y = random()
        angle_z = random()
        angle = random()*10
        time = randint(5,20)
        offset_time = randint(0,time*1000)
        actual_length = random()*length
        points = get_ctrl_points_line(actual_length)
        transforms = [ 
            ('rotate', [('angle', str(angle)), ('x', str(angle_x)), ('y', str(angle_y)), ('z', str(angle_z))], None),
            ('translate', [('time', str(time)), ('align', 'False'), ('draw', 'False'), ('offset',str(offset_time))], points),
            ('scale', [('x','0.02'),('y','0.02'),('z','0.02')], None)
        ]

        draw_group(parent, models, transforms, comment)



def draw_commet(parent):
    a_radius = 100
    b_radius = 60
    models = [sphere]
    comment = 'Commet'
    points = get_ctrl_points_ellipse(a_radius, b_radius) 
    transforms = [ 
        ('rotate', [('angle','15'), ('x','0'), ('y','0'), ('z','1')], None),
        ('translate', [('x','60'), ('y','0'), ('z','0')], None),
        ('translate', [('time', '100'), ('align', 'True'), ('draw', 'True')], points),
        ('scale', [('x','1'),('y','1'),('z','1')], None),
    ]

    commet = draw_group(parent, models, transforms, comment)
    draw_commet_trail(commet)

    return commet


sphere = '../models/sphere.3d'
sphere_very_low_detail = '../models/sphere_very_low_detail.3d'
output = 'solar_system.xml'

if len(argv) == 2:
    output = argv[1]

world = Tree.Element('world')
world.append(Tree.Comment('XML file auto-generated by the solar_system_generator.py script'))

define_camera(world)

draw_sun(world)
draw_mercury(world)
draw_venus(world)
draw_earth(world)
draw_mars(world)
draw_jupiter(world)
draw_saturn(world)
draw_uranus(world)
draw_neptune(world)
draw_commet(world)

tree = Tree.ElementTree(world)
Tree.indent(tree)
tree.write(output)