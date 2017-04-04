//
// Created by cat on 12/13/16.
//

#include "Plot.h"
using namespace std;

Plot::~Plot()
{
}

Plot::Plot(std::string pxHeight,
           std::string pxWidth,
           std::string title,
           std::string png_path,
           std::string plt_path,
           std::string x_Label,
           std::pair<std::string, std::string> x_Range,
           std::string y_Label,
           std::pair<std::string, std::string> y_Range,
           std::string tics,
           bool isNoKey)
{
    m_outPltPath = plt_path;
    m_outPngPath = png_path;
    m_pxHeight = pxHeight;
    m_pxWidth = pxWidth;
    m_title = title;
    m_xLabel = x_Label;
    m_xRange = x_Range;
    m_yLabel = y_Label;
    m_yRange = y_Range;
    m_tics = tics;
    m_IsNoKey = isNoKey;
}

void Plot::SetTerminal()
{
    string str = "set terminal  png size ";
    str += m_pxHeight + "," + m_pxWidth;
    str += " font 'Verdana, 10'";
    m_config.push_back(str);
}

void Plot::SetLegend()
{
    string str = "";
    if (m_IsNoKey)
    {
        str += "set nokey";
        m_config.push_back(str);
    }
}

void Plot::SetTitle()
{
    string str = "set title \"";
    str += m_title;
    str += "\"";
    m_config.push_back(str);
}

void Plot::SetOutputPict()
{
    string str = "set output '";
    str += m_outPngPath;
    str += "'";
    m_config.push_back(str);
}

void Plot::SetYLabel()
{
    string str = "set ylabel \"";
    str += m_yLabel;
    str += "\"";
    m_config.push_back(str);
}

void Plot::SetYRange()
{
    string str = "set yrange [";
    str += m_yRange.first + ":" + m_yRange.second + "]";
    m_config.push_back(str);
}

void Plot::SetXLabel()
{
    string str = "set xlabel \"";
    str += m_xLabel;
    str += "\"";
    m_config.push_back(str);
}

void Plot::SetXRange()
{
    string str = "set xrange [";
    str += m_xRange.first + ":" + m_xRange.second + "]";
    m_config.push_back(str);
}

void Plot::SetGrid()
{
    string str = "set grid xtics ytics";
    m_config.push_back(str);
}

void Plot::AppendPlotLine(const std::string &line)
{
    m_config.push_back(line);
}

void Plot::DoPlot()
{
    SetTerminal();
    SetLegend();
    SetTitle();
    SetOutputPict();
    SetYLabel();
    SetYRange();
    SetXLabel();
    SetXRange();
    SetGrid();
    for (int i = 0; i < m_command_lines.size(); i++)
    {
        AppendPlotLine(m_command_lines[i]);
    }
    Utils::WriteLines(m_outPltPath, m_config);
    Utils::ExecuteCmd(string("gnuplot \"" + m_outPltPath + "\""));
}