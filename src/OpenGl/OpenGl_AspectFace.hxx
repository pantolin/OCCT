// Created on: 2011-07-13
// Created by: Sergey ZERCHANINOV
// Copyright (c) 2011-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.

#ifndef _OpenGl_AspectFace_Header
#define _OpenGl_AspectFace_Header

#include <InterfaceGraphic_telem.hxx>
#include <Aspect_InteriorStyle.hxx>
#include <TCollection_AsciiString.hxx>

#include <OpenGl_AspectLine.hxx>
#include <OpenGl_Element.hxx>
#include <Handle_OpenGl_Texture.hxx>

#include <Graphic3d_TextureMap.hxx>
#include <Graphic3d_AspectFillArea3d.hxx>
#include <Handle_Graphic3d_TextureParams.hxx>

#define OPENGL_AMBIENT_MASK  (1<<0)
#define OPENGL_DIFFUSE_MASK  (1<<1)
#define OPENGL_SPECULAR_MASK (1<<2)
#define OPENGL_EMISSIVE_MASK (1<<3)

class CALL_DEF_CONTEXTFILLAREA;

struct OPENGL_SURF_PROP
{
  float        amb, diff, spec, emsv;
  float        trans, shine;
  float        env_reflexion;
  int          isphysic;
  unsigned int color_mask;
  TEL_COLOUR speccol, difcol, ambcol, emscol, matcol;
  DEFINE_STANDARD_ALLOC
};

class OpenGl_AspectFace : public OpenGl_Element
{

public:

  OpenGl_AspectFace();

  //! Copy parameters
  void SetAspect (const CALL_DEF_CONTEXTFILLAREA& theAspect);
  void SetAspect (const Handle(Graphic3d_AspectFillArea3d)& theAspect);

  //! Set edge aspect.
  void SetAspectEdge (const OpenGl_AspectLine* theAspectEdge)
  {
    myAspectEdge = *theAspectEdge;
  }

  //! @return edge aspect.
  const OpenGl_AspectLine* AspectEdge() const 
  {
    return &myAspectEdge;
  }

  //! @return interior style
  const Aspect_InteriorStyle InteriorStyle() const
  {
    return myInteriorStyle;
  }

  Aspect_InteriorStyle& ChangeInteriorStyle()
  {
    return myInteriorStyle;
  }

  //! @return edge on flag.
  int Edge() const
  {
    return myEdge;
  }

  //! @return edge on flag.
  int& ChangeEdge()
  {
    return myEdge;
  }

  //! @return hatch type.
  int Hatch() const
  {
    return myHatch;
  }

  //! @return hatch type variable.
  int& ChangeHatch()
  {
    return myHatch;
  }

  //! @return distinguishing mode.
  int DistinguishingMode() const
  {
    return myDistinguishingMode;
  }

  //! @return distinguishing mode.
  int& ChangeDistinguishingMode()
  {
    return myDistinguishingMode;
  }

  //! @return culling mode.
  int CullingMode() const
  {
    return myCullingMode;
  }

  //! @return culling mode.
  int& ChangeCullingMode()
  {
    return myCullingMode;
  }

  //! @return front material properties.
  const OPENGL_SURF_PROP& IntFront() const
  {
    return myIntFront;
  }

  //! @return front material properties.
  OPENGL_SURF_PROP& ChangeIntFront()
  {
    return myIntFront;
  }

  //! @return back material properties.
  const OPENGL_SURF_PROP& IntBack() const
  {
    return myIntBack;
  }

  //! @return back material properties.
  OPENGL_SURF_PROP& ChangeIntBack()
  {
    return myIntBack;
  }

  //! @return polygon offset parameters.
  const TEL_POFFSET_PARAM& PolygonOffset() const
  {
    return myPolygonOffset;
  }

  //! @return polygon offset parameters.
  TEL_POFFSET_PARAM& ChangePolygonOffset()
  {
    return myPolygonOffset;
  }

  //! @return texture mapping flag.
  bool DoTextureMap() const
  {
    return myDoTextureMap;
  }

  //! @return texture mapping flag.
  bool& ChangeDoTextureMap()
  {
    return myDoTextureMap;
  }

  //! @return texture map.
  const Handle(OpenGl_Texture)& TextureRes (const Handle(OpenGl_Workspace)& theWorkspace) const
  {
    if (!myIsTextureInit)
    {
      buildTexture (theWorkspace);
      myIsTextureInit = Standard_True;
    }

    return myTextureRes;
  }

  //! @return texture mapping parameters.
  const Handle(Graphic3d_TextureParams)& TextureParams() const
  {
    return myTextureMap->GetParams();
  }

  virtual void Render  (const Handle(OpenGl_Workspace)& theWorkspace) const;
  virtual void Release (const Handle(OpenGl_Context)&   theContext);

protected:

  void buildTexture (const Handle(OpenGl_Workspace)& theWorkspace) const;
  void convertMaterial (const CALL_DEF_MATERIAL& theMat,
                        OPENGL_SURF_PROP&        theSurf);

protected: //! @name ordinary aspect properties

  Aspect_InteriorStyle            myInteriorStyle;
  int                             myEdge;
  int                             myHatch;
  int                             myDistinguishingMode;
  int                             myCullingMode;
  OPENGL_SURF_PROP                myIntFront;
  OPENGL_SURF_PROP                myIntBack;
  TEL_POFFSET_PARAM               myPolygonOffset;
  bool                            myDoTextureMap;
  Handle(Graphic3d_TextureMap)    myTextureMap;

protected: //! @name OpenGl resources

  mutable Standard_Boolean        myIsTextureInit;
  mutable Handle(OpenGl_Texture)  myTextureRes;
  mutable TCollection_AsciiString myTextureId;

protected:

  OpenGl_AspectLine               myAspectEdge;

public:

  DEFINE_STANDARD_ALLOC

};

#endif //_OpenGl_AspectFace_Header
