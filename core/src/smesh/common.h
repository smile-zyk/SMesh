#pragma once

enum InteractionState
{
    kNormal = 0,
    kStart = 1 << 0,
    kRotate = 1 << 1,
    kMove = 1 << 2,
};

enum class RenderMode
{
    // Object Mode
    kObject = 0,
    // Edit Mode
    kWireframe = 1 << 0,
};

enum class GizmoMode
{
    kTranslate = 0,
    kRotate = 1 << 0,
    kScale = 1 << 1,
    kTransform = 1 << 2
};

enum RotationMode
{
    kEulerXYZ = 0,
    kEulerXZY = 1,
    kEulerYXZ = 2,
    kEulerYZX = 3,
    kEulerZXY = 4,
    kEulerZYX = 5,
    kAxisAngle = 6,
    kQuaternion = 7,
};

enum EulerMode
{
    kXYZ = 0,
    kXZY = 1,
    kYXZ = 2,
    kYZX = 3,
    kZXY = 4,
    kZYX = 5,
};