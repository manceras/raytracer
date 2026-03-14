import bpy
from mathutils import Vector

output_path = bpy.path.abspath("//config.toml")

cam = bpy.context.scene.camera
if cam is None:
    print("ERROR: No active camera in scene")
else:
    cam_data = cam.data
    cam_pos = cam.location

    # Camera looks down its local -Z axis
    forward = cam.matrix_world.to_quaternion() @ Vector((0, 0, -1))
    look_at = cam_pos + forward

    # Focal length conversion: focal_blender / sensor_width
    focal_length = cam_data.lens / cam_data.sensor_width

    lines = []
    lines.append("[camera]")
    lines.append(f"position = [{cam_pos.x:.4f}, {cam_pos.z:.4f}, {-cam_pos.y:.4f}]")
    lines.append(f"look_at = [{look_at.x:.4f}, {look_at.z:.4f}, {-look_at.y:.4f}]")
    lines.append(f"focal_length = {focal_length:.4f}")
    lines.append("")

    # Render settings from Blender
    render = bpy.context.scene.render
    lines.append("[render]")
    lines.append(f"width = {render.resolution_x}")
    lines.append(f"height = {render.resolution_y}")
    lines.append("scale = 1")
    lines.append("")

    # Export all point lights
    for obj in bpy.context.scene.objects:
        if obj.type == 'LIGHT' and obj.data.type == 'POINT':
            pos = obj.location
            color = obj.data.color
            energy = obj.data.energy
            r = color.r * energy
            g = color.g * energy
            b = color.b * energy
            lines.append("[[lights]]")
            lines.append(f"position = [{pos.x:.4f}, {pos.z:.4f}, {-pos.y:.4f}]")
            lines.append(f"color = [{r:.4f}, {g:.4f}, {b:.4f}]")
            lines.append("")

    # Model path (keep current or set default)
    lines.append("[model]")
    lines.append('file = "./3d_files/Spheres.obj"')
    lines.append("")

    toml_content = "\n".join(lines)

    with open(output_path, "w") as f:
        f.write(toml_content)

    print(f"Config exported to {output_path}")
    print(toml_content)
