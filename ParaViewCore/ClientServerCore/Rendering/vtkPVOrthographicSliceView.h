/*=========================================================================

  Program:   ParaView
  Module:    vtkPVOrthographicSliceView.h

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPVOrthographicSliceView -- vtkView subclass for Orthographic Slice
// View.
// .SECTION Description
// vtkPVOrthographicSliceView extends vtkPVMultiSliceView to support showing a
// quad-view with orthographic views along with the 3D view. Work with
// vtkPVCompositeOrthographicSliceRepresentation and vtkGeometrySliceRepresentation,
// this class create a 3 slices for any dataset shown in this view and shows
// those slices in the orthographic views. The orthographic views themselves are
// non-composited i.e. the data is simply cloned on all rendering processes
// (hence we limit ourselves to showing slices alone).
//
// .SECTION Interactions
// In the orthographic views, users can use the thumb-wheel to change the slice
// plane (in which case the \c SliceIncrements are used to update the slice
// position). Additionally, users can double click in any of the orthographic
// views to move the slice position to that location.
#ifndef __vtkPVOrthographicSliceView_h
#define __vtkPVOrthographicSliceView_h

#include "vtkPVMultiSliceView.h"

class vtkPVOrthographicSliceViewInteractorStyle;

class VTKPVCLIENTSERVERCORERENDERING_EXPORT vtkPVOrthographicSliceView : public vtkPVMultiSliceView
{
public:
  static vtkPVOrthographicSliceView* New();
  vtkTypeMacro(vtkPVOrthographicSliceView, vtkPVMultiSliceView);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Initialize the view with an identifier. Unless noted otherwise, this method
  // must be called before calling any other methods on this class.
  // @CallOnAllProcessess
  virtual void Initialize(unsigned int id);

  // Description:
  // Overridden to ensure that the SlicePositionAxes3D doesn't get used when
  // determine view bounds.
  virtual void Update();

  enum
    {
    SIDE_VIEW = 0,
    TOP_VIEW = 1,
    FRONT_VIEW = 2,

    YZ_PLANE = SIDE_VIEW,
    ZX_PLANE = TOP_VIEW,
    XY_PLANE = FRONT_VIEW,

    AXIAL_VIEW = TOP_VIEW,
    CORONAL_VIEW = FRONT_VIEW,
    SAGITTAL_VIEW = SIDE_VIEW,

    RIGHT_SIDE_VIEW = SIDE_VIEW
    };

  vtkRenderer* GetRenderer(int index);
  using Superclass::GetRenderer;

  virtual void ResetCamera();
  virtual void ResetCamera(double bounds[6]);
  virtual void SetInteractionMode(int mode);
  virtual void SetupInteractor(vtkRenderWindowInteractor*);

  // Description:
  // Set the slice position.
  void SetSlicePosition(double x, double y, double z);
  vtkGetVector3Macro(SlicePosition, double);

  // Description:
  // Set slice increments.
  vtkSetVector3Macro(SliceIncrements, double);

  // Description:
  // Get/Set whether to show slice annotations.
  vtkSetMacro(SliceAnnotationsVisibility, bool);
  vtkGetMacro(SliceAnnotationsVisibility, bool);


  // Description:
  // To avoid confusion, we don't show the center axes at all in this view.
  virtual void SetCenterAxesVisibility(bool){}

  //*****************************************************************
  virtual void SetBackground(double r, double g, double b);
  virtual void SetBackground2(double r, double g, double b);
  virtual void SetBackgroundTexture(vtkTexture* val);
  virtual void SetGradientBackground(int val);
  virtual void SetTexturedBackground(int val);


//BTX
protected:
  vtkPVOrthographicSliceView();
  ~vtkPVOrthographicSliceView();

  virtual void AboutToRenderOnLocalProcess(bool interactive);
  virtual void UpdateCenterAxes();

  vtkNew<vtkRenderer> Renderers[3];
  vtkNew<vtkPVOrthographicSliceViewInteractorStyle> OrthographicInteractorStyle;
  vtkNew<vtkPVCenterAxesActor> SlicePositionAxes2D[3];
  vtkNew<vtkPVCenterAxesActor> SlicePositionAxes3D;
  vtkNew<vtkTextRepresentation> SliceAnnotations[3];

  double SliceIncrements[3];
  double SlicePosition[3];
  bool SliceAnnotationsVisibility;
private:
  vtkPVOrthographicSliceView(const vtkPVOrthographicSliceView&); // Not implemented
  void operator=(const vtkPVOrthographicSliceView&); // Not implemented

  void OnMouseWheelForwardEvent();
  void OnMouseWheelBackwardEvent();
  void MoveSlicePosition(vtkRenderer* ren, double position[3]);

  unsigned long MouseWheelForwardEventId;
  unsigned long MouseWheelBackwardEventId;

  friend class vtkPVOrthographicSliceViewInteractorStyle;

//ETX
};

#endif
