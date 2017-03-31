/******************************************************************************
 * Copyright (c) 2016-2017, Bradley J Chambers (brad.chambers@gmail.com)
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following
 * conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of Hobu, Inc. or Flaxen Geo Consulting nor the
 *       names of its contributors may be used to endorse or promote
 *       products derived from this software without specific prior
 *       written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 ****************************************************************************/

#pragma once

#include <pdal/Filter.hpp>
#include <pdal/plugin.hpp>

#include <map>
#include <memory>
#include <string>

extern "C" int32_t OutlierFilter_ExitFunc();
extern "C" PF_ExitFunc OutlierFilter_InitPlugin();

namespace pdal
{

class Options;

struct Indices
{
    std::vector<PointId> inliers;
    std::vector<PointId> outliers;
};

class PDAL_DLL OutlierFilter : public pdal::Filter
{
public:
    OutlierFilter() : Filter()
    {
    }

    static void* create();
    static int32_t destroy(void*);
    std::string getName() const;

private:
    std::string m_method;
    int m_minK;
    double m_radius;
    int m_meanK;
    double m_multiplier;
    uint8_t m_class;

    virtual void addDimensions(PointLayoutPtr layout);
    virtual void addArgs(ProgramArgs& args);
    Indices processRadius(PointViewPtr inView);
    Indices processStatistical(PointViewPtr inView);
    virtual PointViewSet run(PointViewPtr view);

    OutlierFilter& operator=(const OutlierFilter&); // not implemented
    OutlierFilter(const OutlierFilter&);            // not implemented
};

} // namespace pdal
