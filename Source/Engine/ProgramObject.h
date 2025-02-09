#pragma once
class ProgramObject {
protected:
  unsigned int m_RendererID = 0;

  public:
  virtual ~ProgramObject() = default;
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual unsigned int GetRendererID() const{
    return m_RendererID;
  }
};