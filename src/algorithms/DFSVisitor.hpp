#pragma once

class DFSVisitor {
public:
    virtual ~DFSVisitor() = default;

    virtual void onEnter(int v) {}
    virtual void onExit(int v) {}
    virtual void onEdge(int u, int v) {}
};
