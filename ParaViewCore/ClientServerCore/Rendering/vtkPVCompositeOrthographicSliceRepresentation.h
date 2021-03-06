/*=========================================================================

  Program:   ParaView
  Module:    vtkPVCompositeOrthographicSliceRepresentation.h

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPVCompositeOrthographicSliceRepresentation
// .SECTION Description
// vtkPVCompositeOrthographicSliceRepresentation is designed for use with
// vtkPVOrthographicSliceView. Similar to how we add cube-axes representation
// etc. to vtkPVCompositeRepresentation, we add 3 vtkGeometrySliceRepresentation
// instances to render the 3 slices in vtkPVOrthographicSliceView's orthographic
// views.

#ifndef __vtkPVCompositeOrthographicSliceRepresentation_h
#define __vtkPVCompositeOrthographicSliceRepresentation_h

#include "vtkPVCompositeRepresentation.h"
#include "vtkSmartPointer.h" // needed for vtkSmartPointer.

class VTKPVCLIENTSERVERCORERENDERING_EXPORT vtkPVCompositeOrthographicSliceRepresentation : public vtkPVCompositeRepresentation
{
public:
  static vtkPVCompositeOrthographicSliceRepresentation* New();
  vtkTypeMacro(vtkPVCompositeOrthographicSliceRepresentation, vtkPVCompositeRepresentation);
  void PrintSelf(ostream& os, vtkIndent indent);

  void SetSliceRepresentation(int index, vtkPVDataRepresentation*);

  // Description:
  // Set visibility of the representation.
  // Overridden to update the cube-axes and selection visibilities.
  virtual void SetVisibility(bool visible);

  // Description:
  // Overridden to simply pass the input to the internal representations. We
  // won't need this if vtkDataRepresentation correctly respected in the
  // arguments passed to it during ProcessRequest() etc.
  virtual void SetInputConnection(int port, vtkAlgorithmOutput* input);
  virtual void SetInputConnection(vtkAlgorithmOutput* input);
  virtual void AddInputConnection(int port, vtkAlgorithmOutput* input);
  virtual void AddInputConnection(vtkAlgorithmOutput* input);
  virtual void RemoveInputConnection(int port, vtkAlgorithmOutput* input);
  virtual void RemoveInputConnection(int port, int index);

  // Description:
  // Propagate the modification to all internal representations.
  virtual void MarkModified();

  // Description:
  // Override because of internal composite representations that need to be
  // initilized as well.
  virtual unsigned int Initialize(unsigned int minIdAvailable, unsigned int maxIdAvailable);

//BTX
protected:
  vtkPVCompositeOrthographicSliceRepresentation();
  ~vtkPVCompositeOrthographicSliceRepresentation();

  // Description:
  // Adds the representation to the view.  This is called from
  // vtkView::AddRepresentation().  Subclasses should override this method.
  // Returns true if the addition succeeds.
  virtual bool AddToView(vtkView* view);

  // Description:
  // Removes the representation to the view.  This is called from
  // vtkView::RemoveRepresentation().  Subclasses should override this method.
  // Returns true if the removal succeeds.
  virtual bool RemoveFromView(vtkView* view);

  vtkSmartPointer<vtkPVDataRepresentation> SliceRepresentations[3];

private:
  vtkPVCompositeOrthographicSliceRepresentation(const vtkPVCompositeOrthographicSliceRepresentation&); // Not implemented
  void operator=(const vtkPVCompositeOrthographicSliceRepresentation&); // Not implemented
//ETX
};

#endif
