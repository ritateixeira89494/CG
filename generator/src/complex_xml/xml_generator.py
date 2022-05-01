import xml.etree.ElementTree as Tree

from typing import List, Tuple

world = Tree.Element('world')

camera = Tree.SubElement(world, "camera")

square = ['../models/box.3d']
sphere = ['../models/sphere.3d']
cone = ['../models/cone.3d']


# Camera stuff
def get_camera_element(element):
    # Position
    position = Tree.SubElement(element, 'position')
    position.attrib['x'] = '15'
    position.attrib['y'] = '10'
    position.attrib['z'] = '15'

    # LookAt
    look_at = Tree.SubElement(element, 'lookAt')
    look_at.attrib['x'] = '0'
    look_at.attrib['y'] = '0'
    look_at.attrib['z'] = '0'

    # Up
    up = Tree.SubElement(element, 'up')
    up.attrib['x'] = '1'
    up.attrib['y'] = '1'
    up.attrib['z'] = '1'

    # Projection
    projection = Tree.SubElement(element, 'projection')
    projection.attrib['fov'] = '150'
    projection.attrib['near'] = '1'
    projection.attrib['far'] = '1000'


# [(nome, valor)]
# [('translate', [(x, 10), (y, 0), (z, 0)])]

# List of transformations
# Transformation -> tuple with a name and a list of attributes
# Attributes -> List of attribute
# Attribute -> tuple with the name of the attribute and the value
# [('translate', [('x', '0')]), ('rotate', [('angle', '90')]]
def get_group_element(element, transforms: List[Tuple[str, List[Tuple[str, str]]]], models: List[str]):
    group_elem = Tree.SubElement(element, 'group')
    # Transform stuff
    transform_elem = Tree.SubElement(group_elem, 'transform')
    for (name, values) in transforms:
        elem = Tree.SubElement(transform_elem, name)
        for (attr_name, attr_value) in values:
            elem.attrib[attr_name] = attr_value

    # Model stuff
    models_elem = Tree.SubElement(group_elem, 'models')
    for model in models:
        elem = Tree.SubElement(models_elem, 'model')
        elem.attrib['file'] = model

    return group_elem


get_camera_element(camera)

transforms1 = [
    ('translate', [('x', '1'), ('y', '0'), ('z', '0')]),
    # ('rotate', [('angle', '0'), ('x', '0'), ('y', '0'), ('z', '0')]),
    # ('scale', [('x', '0'), ('y', '0'), ('z', '0')]),
]

models1 = [
    # 'plane.3d',
    square
]


def draw_layer(group, size):
    """
    Draws a layer size by size
    :param group: the group to draw the layer
    :param size: the size
    :return: None
    """
    g = group
    t = []
    for _ in range(size):
        outer_group = get_group_element(g, t, [])

        t = [
            ('translate', [('x', '0'), ('y', '0'), ('z', '2')]),
        ]

        inner_group = outer_group

        # First model without translate
        tr = []

        for _ in range(size):
            m = square

            inner_group = get_group_element(inner_group, tr, m)

            tr = [
                ('translate', [('x', '2'), ('y', '0'), ('z', '0')]),
            ]

        g = outer_group


def draw_pyramid(group, size: int):
    """
    Draws a pyramid
    :return:
    """
    layer = group
    for i in reversed(range(size + 1)[1:]):
        draw_layer(layer, i)
        layer = get_group_element(layer, [
            ('translate', [('x', '0'), ('y', '2'), ('z', '0')])], [])


def draw_4_pyramid(group, size: int):
    gr = group
    for i in range(4):
        gr = get_group_element(gr, [('rotate', [('angle', '90'), ('x', '0'), ('y', '1'), ('z', '0')])], [])
        draw_pyramid(gr, size)


def draw_ovni(piramid_complete):
    piramid_side = [('translate', [('x', '20'), ('y', '20'), ('z', '20')]),
                    ('scale', [('x', '0.2'), ('y', '0.2'), ('z', '0.2')])]
    world = get_group_element(piramid_complete, piramid_side, [])
    group_elem = Tree.SubElement(world, 'group')
    # Sphere part
    sphereUpSize = [
        ('translate', [('x', '0'), ('y', '4'), ('z', '0')]),
        ('scale', [('x', '5'), ('y', '5'), ('z', '5')]),
    ]
    get_group_element(world, sphereUpSize, sphere)
    # Two cones part
    transform_elem = Tree.SubElement(group_elem, 'transform')
    coneOvniScale = [
        ('scale', [('x', '11'), ('y', '3'), ('z', '11')])]

    ovni = get_group_element(world, coneOvniScale, cone)
    rotate = [('rotate', [('angle', '180'), ('x', '1'), ('y', '0'), ('z', '1')])]
    get_group_element(ovni, rotate, cone)
    # One cone part
    coneOutOvniScale = [
        ('translate', [('x', '0'), ('y', '-32'), ('z', '0')]),
        ('scale', [('x', '8'), ('y', '15'), ('z', '8')])]
    posCone = get_group_element(group_elem, coneOutOvniScale, cone)
    # Cube part
    cuboTranslate = [('translate', [('x', '0'), ('y', '-40'), ('z', '0')]),
                     ('scale', [('x', '8'), ('y', '8'), ('z', '8')])
                     ]
    get_group_element(group_elem, cuboTranslate, square)


draw_4_pyramid(world, 10)

draw_ovni(world)
tree = Tree.ElementTree(world)

tree.write('generated.xml')
