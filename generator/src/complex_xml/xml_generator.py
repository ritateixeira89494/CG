import xml.etree.cElementTree as Tree

from typing import List, Tuple

world = Tree.Element('world')

camera = Tree.SubElement(world, "camera")


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
    # ('rotate', [('angle', '0'), ('x', '0'), ('y', '0'), ('y', '0')]),
    # ('scale', [('x', '0'), ('y', '0'), ('y', '0')]),
]

models1 = [
    # 'plane.3d',
    'box.3d'
]


def draw_layer(group, size):
    """
    Draws a layer size by size
    :param group: the group to draw the layer
    :param size: the size
    :return: None
    """
    g = group
    for _ in range(size):
        t = [
            ('translate', [('x', '0'), ('y', '0'), ('z', '2')]),
        ]
        outer_group = get_group_element(g, t, [])

        inner_group = outer_group
        for _ in range(size):
            t = [
                ('translate', [('x', '2'), ('y', '0'), ('z', '0')]),
            ]

            m = ['box.3d']

            gr = get_group_element(inner_group, t, m)
            inner_group = gr

        g = outer_group


def draw_pyramid(group, size: int):
    """
    Draws a pyramid
    :return:
    """
    layer = group
    for i in reversed(range(size)):
        draw_layer(layer, i)
        layer = get_group_element(layer, [
            ('translate', [('x', '0'), ('y', '2'), ('z', '0')])], [])


draw_pyramid(world, 10)

tree = Tree.ElementTree(world)

tree.write('generated.xml')
