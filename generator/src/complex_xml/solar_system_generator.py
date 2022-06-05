from random import random, randint
import xml.etree.cElementTree as Tree
from numpy import pi, sin, cos
from sys import argv, version_info

ambient = (40, 40, 40)

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


def set_colors(color_elem, diff_rgb, amb_rgb, spec_rgb, emiss_rgb, shininess):
    diff = Tree.SubElement(color_elem, 'diffuse')
    diff.attrib['R'] = str(diff_rgb[0])
    diff.attrib['G'] = str(diff_rgb[1])
    diff.attrib['B'] = str(diff_rgb[2])

    amb = Tree.SubElement(color_elem, 'ambient')
    amb.attrib['R'] = str(amb_rgb[0])
    amb.attrib['G'] = str(amb_rgb[1])
    amb.attrib['B'] = str(amb_rgb[2])

    spec = Tree.SubElement(color_elem, 'specular')
    spec.attrib['R'] = str(spec_rgb[0])
    spec.attrib['G'] = str(spec_rgb[1])
    spec.attrib['B'] = str(spec_rgb[2])

    emiss = Tree.SubElement(color_elem, 'emissive')
    emiss.attrib['R'] = str(emiss_rgb[0])
    emiss.attrib['G'] = str(emiss_rgb[1])
    emiss.attrib['B'] = str(emiss_rgb[2])

    shine = Tree.SubElement(color_elem, 'shininess')
    shine.attrib['value'] = str(shininess)


def add_light(world):
    lights = Tree.SubElement(world, 'lights')
    comment = 'Sun ilumination'
    lights.append(Tree.Comment(comment))

    light_elem = Tree.SubElement(lights, 'light')
    light_elem.attrib['type'] = 'point'
    light_elem.attrib['posX'] = '0'
    light_elem.attrib['posY'] = '0'
    light_elem.attrib['posZ'] = '0'


def draw_group(parent, models=None, diff_rgb=(255, 255, 255), amb_rgb=(255, 255, 255), spec_rgb=(255, 255, 255),
               emiss_rgb=(255, 255, 255), shininess=128, transforms=None, comment=None):
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
    for model, texture in models:
        model_elem = Tree.SubElement(models_elem, 'model')
        model_elem.attrib['file'] = model

        texture_elem = Tree.SubElement(model_elem, 'texture')

        texture_elem.attrib['file'] = texture

        color_elem = Tree.SubElement(model_elem, 'color')
        set_colors(color_elem, diff_rgb, amb_rgb, spec_rgb, emiss_rgb, shininess)

    return group


def get_ctrl_points_circle(radius, num=16):
    points = []
    for i in range(num):
        angle = -((i / num) * 2 * pi)
        x = cos(angle) * radius
        y = 0
        z = sin(angle) * radius

        points.append(('point', [('x', str(x)), ('y', str(y)), ('z', str(z))]))

    return points


def get_ctrl_points_ellipse(a_radius, b_radius, num=16):
    points = []
    for i in range(num):
        angle = -((i / num) * 2 * pi)  # Here we are flipping
        x = cos(angle) * a_radius
        y = 0
        z = sin(angle) * b_radius

        points.append(('point', [('x', str(x)), ('y', str(y)), ('z', str(z))]))

    return points


def get_ctrl_points_line(length, num=4):
    points = []
    for i in range(num):
        x = -(i * length / num)
        y = 0
        z = 0

        points.append(('point', [('x', str(x)), ('y', str(y)), ('z', str(z))]))

    return points


def draw_sun(parent):
    models = [(sphere, "../textures/sun.jpg")]
    comment = 'Sun'

    transforms = [
        ('scale', [('x', '15'), ('y', '15'), ('z', '15')], None),
        ('rotate', [('time', '60'), ('x', '0'), ('y', '1'), ('z', '0')], None)
    ]
    diffuse = (252, 229, 112)
    global ambient
    specular = (255, 255, 255)
    emissive = (252, 229, 112)
    shininess = 128

    return draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)


def draw_mercury(parent):
    radius = 25
    models = [(sphere, "../textures/mercury.jpg")]
    comment = 'Mercury'
    points = get_ctrl_points_circle(radius)
    transforms = [
        ('translate', [('time', '15'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '10'), ('x', '0'), ('y', '1'), ('z', '0')], None),
        ('scale', [('x', '0.49'), ('y', '0.49'), ('z', '0.49')], None),
    ]
    diffuse = (128, 128, 128)
    global ambient
    specular = (255, 255, 255)
    emissive = (0, 0, 0)
    shininess = 128

    return draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)


def draw_venus(parent):
    radius = 30
    models = [(sphere, "../textures/venus.jpg")]
    comment = 'Venus'
    points = get_ctrl_points_circle(radius)
    transforms = [
        ('translate', [('time', '20'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '15'), ('x', '0'), ('y', '-1'), ('z', '0')], None),
        ('scale', [('x', '1.21'), ('y', '1.21'), ('z', '1.21')], None)
    ]
    diffuse = (255, 198, 73)
    global ambient
    specular = (255, 255, 255)
    emissive = (0, 0, 0)
    shininess = 128

    return draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)


def draw_earth(parent):
    radius = 35
    models = [(sphere, "../textures/earth.jpg")]
    comment = 'Earth'
    points = get_ctrl_points_circle(radius)
    transforms = [
        ('translate', [('time', '25'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '13'), ('x', '0'), ('y', '1'), ('z', '0')], None),
        ('scale', [('x', '1.27'), ('y', '1.27'), ('z', '1.27')], None),
    ]
    diffuse = (79, 76, 176)
    global ambient
    specular = (255, 255, 255)
    emissive = (0, 0, 0)
    shininess = 128

    earth = draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)
    draw_moon(earth)

    return earth


def draw_moon(parent):
    radius = 5
    models = [(sphere, "../textures/moon.jpg")]
    comment = 'Moon'
    points = get_ctrl_points_circle(radius)
    transforms = [
        ('translate', [('time', '10'), ('align', 'True'), ('draw', 'True')], points),
        ('scale', [('x', '0.35'), ('y', '0.35'), ('z', '0.35')], None),
    ]
    diffuse = (148, 144, 141)
    global ambient
    specular = (255, 255, 255)
    emissive = (0, 0, 0)
    shininess = 128

    return draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)


def draw_mars(parent):
    radius = 45
    models = [(sphere, "../textures/mars.jpg")]
    comment = 'Mars'
    points = get_ctrl_points_circle(radius)
    transforms = [
        ('translate', [('time', '35'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '10'), ('x', '0'), ('y', '1'), ('z', '0')], None),
        ('scale', [('x', '0.68'), ('y', '0.68'), ('z', '0.68')], None),
    ]
    diffuse = (226, 123, 88)
    global ambient
    specular = (255, 255, 255)
    emissive = (0, 0, 0)
    shininess = 128

    return draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)


def draw_jupiter(parent):
    radius = 55
    models = [(sphere, "../textures/jupiter.jpg")]
    comment = 'Jupiter'
    points = get_ctrl_points_circle(radius)
    transforms = [
        ('translate', [('time', '45'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '30'), ('x', '0'), ('y', '1'), ('z', '0')], None),
        ('scale', [('x', '5'), ('y', '5'), ('z', '5')], None),
    ]
    diffuse = (211, 156, 126)
    global ambient
    specular = (255, 255, 255)
    emissive = (0, 0, 0)
    shininess = 128

    return draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)


def draw_saturn(parent):
    radius = 70
    models = [(sphere, "../textures/saturn.jpg")]
    comment = 'Saturn'
    points = get_ctrl_points_circle(radius)
    transforms = [
        ('translate', [('time', '55'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '35'), ('x', '0'), ('y', '1'), ('z', '0')], None),
        ('scale', [('x', '3.5'), ('y', '3.5'), ('z', '3.5')], None),
    ]
    asteroids = 1000
    diffuse = (52, 62, 71)
    global ambient
    specular = (255, 255, 255)
    emissive = (0, 0, 0)
    shininess = 128

    saturn = draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)

    for i in range(asteroids):
        radius = random() + 2
        translate_time = randint(10, 40)
        rotation = randint(0, 360)
        draw_saturn_asteroid(saturn, radius, translate_time, rotation)

    return saturn


def draw_saturn_asteroid(parent, radius, translate_time, rotation):
    models = [(sphere_very_low_detail, "")]
    comment = 'Saturn Asteroid'
    points = get_ctrl_points_circle(radius)
    transforms = [
        ('rotate', [('time', '35'), ('x', '0'), ('y', '-1'), ('z', '0')], None),  # Undo rotation applied to Saturn
        ('rotate', [('angle', str(rotation)), ('x', '0'), ('y', '1'), ('z', '0')], None),
        ('translate', [('time', str(translate_time)), ('align', 'False'), ('draw', 'False')], points),
        ('scale', [('x', '0.01'), ('y', '0.01'), ('z', '0.01')], None),
    ]
    diffuse = (118, 118, 118)
    global ambient
    specular = (255, 255, 255)
    emissive = (0, 0, 0)
    shininess = 128

    return draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)


def draw_uranus(parent):
    radius = 85
    models = [(sphere, "../textures/uranus.jpg")]
    comment = 'Uranus'
    points = get_ctrl_points_circle(radius)
    transforms = [
        ('translate', [('time', '65'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '40'), ('x', '0'), ('y', '-1'), ('z', '0')], None),
        ('scale', [('x', '2.57'), ('y', '2.57'), ('z', '2.57')], None),
    ]
    diffuse = (101, 134, 139)
    global ambient
    specular = (255, 255, 255)
    emissive = (0, 0, 0)
    shininess = 128

    return draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)


def draw_neptune(parent):
    radius = 95
    models = [(sphere, "../textures/neptune.jpg")]
    comment = 'Neptune'
    points = get_ctrl_points_circle(radius)
    transforms = [
        ('translate', [('time', '75'), ('align', 'False'), ('draw', 'True')], points),
        ('rotate', [('time', '45'), ('x', '0'), ('y', '1'), ('z', '0')], None),
        ('scale', [('x', '2.27'), ('y', '2.27'), ('z', '2.27')], None),
    ]
    diffuse = (91, 93, 223)
    global ambient
    specular = (255, 255, 255)
    emissive = (0, 0, 0)
    shininess = 128

    return draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)


def draw_comet_trail(parent):
    length = 40
    models = [(sphere_very_low_detail, "")]
    comment = 'Comet Trail'
    trail_num = 1000

    for i in range(trail_num):
        angle_x = random()
        angle_y = random()
        angle_z = random()
        angle = random() * 10
        time = randint(5, 20)
        offset_time = randint(0, time * 1000)
        actual_length = random() * length
        points = get_ctrl_points_line(actual_length)
        transforms = [
            ('rotate', [('angle', str(angle)), ('x', str(angle_x)), ('y', str(angle_y)), ('z', str(angle_z))], None),
            ('translate', [('time', str(time)), ('align', 'False'), ('draw', 'False'), ('offset', str(offset_time))],
             points),
            ('scale', [('x', '0.02'), ('y', '0.02'), ('z', '0.02')], None)
        ]
        diffuse = (118, 118, 118)
        global ambient
        specular = (255, 255, 255)
        emissive = (0, 0, 0)
        shininess = 128

        draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)


def draw_comet(parent):
    a_radius = 100
    b_radius = 60
    models = [(comet_path, "../textures/moon.jpg")]
    comment = 'Comet'
    points = get_ctrl_points_ellipse(a_radius, b_radius)
    transforms = [
        ('rotate', [('angle', '15'), ('x', '0'), ('y', '0'), ('z', '1')], None),
        ('translate', [('x', '60'), ('y', '0'), ('z', '0')], None),
        ('translate', [('time', '100'), ('align', 'True'), ('draw', 'True')], points),
        ('scale', [('x', '1'), ('y', '1'), ('z', '1')], None),
    ]
    diffuse = (118, 118, 118) 
    global ambient
    specular = (255, 255, 255)
    emissive = (0, 0, 0)
    shininess = 128

    comet = draw_group(parent, models, diffuse, ambient, specular, emissive, shininess, transforms, comment)
    draw_comet_trail(comet)

    return comet


sphere = '../models/sphere.3d'
sphere_very_low_detail = '../models/sphere_very_low_detail.3d'
output = 'solar_system.xml'
comet_path = '../models/teapot.3d'

if len(argv) == 2:
    output = argv[1]

world = Tree.Element('world')
world.append(Tree.Comment('XML file auto-generated by the solar_system_generator.py script'))

define_camera(world)
add_light(world)

draw_sun(world)
draw_mercury(world)
draw_venus(world)
draw_earth(world)
draw_mars(world)
draw_jupiter(world)
draw_saturn(world)
draw_uranus(world)
draw_neptune(world)
draw_comet(world)

tree = Tree.ElementTree(world)

if version_info >= (3, 9):  # This method is only available in Python >= 3.9
    print(f'Running Python {version_info.major}.{version_info.minor}. Indenting feature active...')
    Tree.indent(tree)
else:
    print(
        f'Running Python {version_info.major}.{version_info.minor}. Indenting feature disabled... (Minimum version required: Python 3.9)')

tree.write(output)
