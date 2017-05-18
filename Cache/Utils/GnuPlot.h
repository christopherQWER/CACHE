//
// Created by cat on 12/13/16.
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Utils.h"

class GnuPlot {
public:
    std::string m_pxHeight;
    std::string m_pxWidth;
    std::string m_title;
    std::string m_outPngPath;
    std::string m_outPltPath;
    std::string m_xLabel;
    std::pair<std::string, std::string> m_xRange;
    std::string m_yLabel;
    std::pair<std::string, std::string> m_yRange;
    std::string m_tics;
    bool m_IsNoKey;
    std::vector<std::string> m_command_lines;

    std::vector<std::string> m_config;

    GnuPlot(std::string pxHeight,
         std::string pxWidth,
         std::string title,
         std::string png_path,
         std::string plt_path,
         std::string x_Label,
         std::pair<std::string, std::string> x_Range,
         std::string y_Label,
         std::pair<std::string, std::string> y_Range,
         std::string tics,
         bool isNoKey);
    ~GnuPlot();

    void SetTerminal();
    void SetLegend();
    void SetTitle();
    void SetOutputPict();
    void SetYLabel();
    void SetYRange();
    void SetXLabel();
    void SetXRange();
    void SetGrid();
    void AppendPlotLine(const std::string &line);

    void DoPlot();
};
