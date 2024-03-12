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