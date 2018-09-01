import math
import numpy as np
import rtx
import matplotlib.pyplot as plt

scene = rtx.Scene()

box_size = 6

# 1
geometry = rtx.PlainGeometry(box_size, box_size)
material = rtx.MeshLambertMaterial((1.0, 1.0, 1.0), 1.0)
wall = rtx.Mesh(geometry, material)
wall.set_rotation((0, 0, 0))
wall.set_position((0, 0, -box_size / 2))
scene.add(wall)

# 2
geometry = rtx.PlainGeometry(box_size, box_size)
material = rtx.MeshLambertMaterial((1.0, 0.0, 0.0), 1.0)
wall = rtx.Mesh(geometry, material)
wall.set_rotation((0, -math.pi / 2, 0))
wall.set_position((box_size / 2, 0, 0))
scene.add(wall)

# 3
geometry = rtx.PlainGeometry(box_size, box_size)
material = rtx.MeshLambertMaterial((0.0, 1.0, 0.0), 1.0)
wall = rtx.Mesh(geometry, material)
wall.set_rotation((0, math.pi / 2, 0))
wall.set_position((-box_size / 2, 0, 0))
scene.add(wall)

# 4
geometry = rtx.PlainGeometry(box_size, box_size)
material = rtx.MeshLambertMaterial((1.0, 1.0, 1.0), 1.0)
wall = rtx.Mesh(geometry, material)
wall.set_rotation((0, math.pi, 0))
wall.set_position((0, 0, box_size / 2))
scene.add(wall)

# ceil
geometry = rtx.PlainGeometry(box_size, box_size)
material = rtx.MeshLambertMaterial((1.0, 1.0, 1.0), 1.0)
ceil = rtx.Mesh(geometry, material)
ceil.set_rotation((math.pi / 2, 0, 0))
ceil.set_position((0, box_size / 2, 0))
scene.add(ceil)

# floor
geometry = rtx.PlainGeometry(box_size, box_size)
material = rtx.MeshLambertMaterial((1.0, 1.0, 1.0), 1.0)
ceil = rtx.Mesh(geometry, material)
ceil.set_rotation((-math.pi / 2, 0, 0))
ceil.set_position((0, -box_size / 2, 0))
scene.add(ceil)

# light
geometry = rtx.PlainGeometry(box_size / 4, box_size / 4)
material = rtx.MeshEmissiveMaterial(color=(1.0, 1.0, 1.0))
light = rtx.Mesh(geometry, material)
light.set_rotation((math.pi / 2, 0, 0))
light.set_position((0, box_size / 2 - 0.01, 0))
scene.add(light)

# place ball
geometry = rtx.SphereGeometry(0.8)
material = rtx.MeshLambertMaterial(color=(1.0, 1.0, 1.0), diffuse_reflectance=1.0)
sphere = rtx.Mesh(geometry, material)
sphere.set_position((1.5, -box_size / 2 + 1, 0.5))
scene.add(sphere)

# place boxes
geometry = rtx.BoxGeometry(1.6, 1.6, 1.6)
material = rtx.MeshLambertMaterial(color=(1.0, 1.0, 1.0), diffuse_reflectance=1.0)
box = rtx.Mesh(geometry, material)
box.set_position((-1, -box_size / 2 + 0.8, 1))
box.set_rotation((0, math.pi / 5, 0))
scene.add(box)

geometry = rtx.BoxGeometry(1.6, 3.2, 1.6)
material = rtx.MeshLambertMaterial(color=(1.0, 1.0, 1.0), diffuse_reflectance=1.0)
box = rtx.Mesh(geometry, material)
box.set_position((-1, -box_size / 2 + 1.6, -1))
box.set_rotation((0, math.pi / 5, 0))
scene.add(box)

screen_width = 512
screen_height = 512

render_options = rtx.RayTracingOptions()
render_options.num_rays_per_pixel = 512
render_options.path_depth = 5

renderer = rtx.RayTracingCUDARenderer()
camera = rtx.PerspectiveCamera(
    eye=(0, 0, -1),
    center=(0, 0, 0),
    up=(0, 1, 0),
    fov_rad=math.pi / 3,
    aspect_ratio=screen_width / screen_height,
    z_near=0.01,
    z_far=100)

render_buffer = np.zeros((screen_height, screen_width, 3), dtype="float32")
# renderer.render(scene, camera, render_options, render_buffer)
camera_rad = 0
# camera_rad = math.pi / 10
radius = 5.5
while True:
    eye = (radius * math.sin(camera_rad), 0.0, radius * math.cos(camera_rad))
    camera.look_at(eye=eye, center=(0, 0, 0), up=(0, 1, 0))

    renderer.render(scene, camera, render_options, render_buffer)
    # linear -> sRGB
    pixels = np.power(np.clip(render_buffer, 0, 1), 1.0 / 2.2)
    # display
    plt.imshow(pixels, interpolation="none")
    plt.pause(1e-8)

    camera_rad += math.pi / 10
