/*=========================================================================

  Program:   Visualization Toolkit

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

   This software is distributed WITHOUT ANY WARRANTY; without even
   the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
   PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "vtkFeatureLayer.h"

#include "vtkFeature.h"

#include <vtkObjectFactory.h>

#include <algorithm>
#include <iterator>
#include <vector>

vtkStandardNewMacro(vtkFeatureLayer);

//----------------------------------------------------------------------------
class vtkFeatureLayer::vtkInternal
{
public:
  std::vector<vtkFeature*> Features;
};

//----------------------------------------------------------------------------
vtkFeatureLayer::vtkFeatureLayer()
{
}

//----------------------------------------------------------------------------
vtkFeatureLayer::~vtkFeatureLayer()
{
}

//----------------------------------------------------------------------------
void vtkFeatureLayer::PrintSelf(std::ostream& os, vtkIndent indent)
{
  // TODO
}

//----------------------------------------------------------------------------
void vtkFeatureLayer::AddFeature(vtkFeature* feature)
{
  if (!feature)
    {
    return;
    }

  std::vector<vtkFeature*>::iterator itr = std::find(
    this->Impl->Features.begin(), this->Impl->Features.end(), feature);
  if (itr == this->Impl->Features.end())
    {
    feature->SetLayer(this);
    this->Impl->Features.push_back(feature);
    }

  this->Modified();
}

//----------------------------------------------------------------------------
void vtkFeatureLayer::RemoveFeature(vtkFeature* feature)
{
  if (!feature)
    {
    return;
    }

  feature->SetLayer(0);
  this->Impl->Features.erase(std::remove(this->Impl->Features.begin(),
                             this->Impl->Features.end(), feature));
}

//----------------------------------------------------------------------------
void vtkFeatureLayer::Update()
{
  for (size_t i = 0; i < this->Impl->Features.size(); i += 1)
    {
    this->Impl->Features[i]->Update();
    }
}
