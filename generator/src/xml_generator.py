import xml.etree.cElementTree as Tree

from typing import List, Tuple

root = Tree.Element('world')

camera = Tree.SubElement(root, "camera")
group = Tree.SubElement(root, 'group')


# Camera stuff
def get_camera_element(element):
    # Position
    position = Tree.SubElement(element, 'position')
    position.attrib['x'] = '0'
    position.attrib['y'] = '0'
    position.attrib['z'] = '0'

    # LookAt
    look_at = Tree.SubElement(element, 'lookAt')
    look_at.attrib['x'] = '0'
    look_at.attrib['y'] = '0'
    look_at.attrib['z'] = '0'

    # Up
    up = Tree.SubElement(element, 'up')
    up.attrib['x'] = '0'
    up.attrib['y'] = '0'
    up.attrib['z'] = '0'

    # Projection
    projection = Tree.SubElement(element, 'projection')
    projection.attrib['fov'] = '60'
    projection.attrib['near'] = '1'
    projection.attrib['far'] = '1000'


# [(nome, valor)]
# [Translação x = 10, y = 0, z = 0)]
# [(Translação, [(x, 10), (y, 0), (z, 0)])]
# list[tuple[str, tuple[str, str]]]

# List of transformations
# Transformation -> tuple with a name and a list of attributes
# Attributes -> List of attribute
# Attribute -> tuple with the name of the attribute and the value
# [('translate', [('x', '0')])]
def get_group_element(element, transforms: List[Tuple[str, List[Tuple[str, str]]]], models: List[str]):
    # Transform stuff
    transform_elem = Tree.SubElement(element, 'transform')
    for (name, values) in transforms:
        elem = Tree.SubElement(transform_elem, name)
        for (attr_name, attr_value) in values:
            elem.attrib[attr_name] = attr_value

    # Model stuff
    models_elem = Tree.SubElement(element, 'models')
    for model in models:
        elem = Tree.SubElement(models_elem, 'model')
        elem.attrib['file'] = model


get_camera_element(camera)

transforms1 = [
    ('translate', [('x', '20')]),
    ('rotate', [('angle', '0'), ('x', '0'), ('y', '0'), ('y', '0')]),
    ('scale', [('x', '0'), ('y', '0'), ('y', '0')]),
]

models1 = [
    'plane.3d',
    'box.3d'
]

get_group_element(group, transforms1, models1)

tree = Tree.ElementTree(root)

tree.write('diogo.xml')
