#include "image_work.h"


void Image::rectangle(Rectangle & rect)
{
    if (rect.left_up[0] >= bm_width)
    {
        rect.left_up[0] = bm_width - 1;
    }
    if (rect.left_up[1] >= bm_height)
    {
        rect.left_up[1] = bm_height - 1;
    }
    if (rect.right_down[0] >= bm_width)
    {
        rect.right_down[0] = bm_width - 1;
    }
    if (rect.right_down[1] >= bm_height)
    {
        rect.right_down[1] = bm_height - 1;
    }

    if (rect.left_up[0] > rect.right_down[0])
    {
        int tmp = rect.left_up[0];
        rect.left_up[0] = rect.right_down[0];
        rect.right_down[0] = tmp;
    }
    if (rect.left_up[1] < rect.right_down[1])
    {
        int tmp = rect.left_up[1];
        rect.left_up[1] = rect.right_down[1];
        rect.right_down[1] = tmp;
    }
    int x1, y1, x2, y2;
    
    for (int k = 0; k < rect.thickness; k++)
    {
        x1 = rect.left_up[0] + k;
        y1 = rect.left_up[1] - k;
        x2 = rect.right_down[0] - k;
        y2 = rect.right_down[1] + k;
        std::cout << x1 << ' ' << x2 << ' ' << y1 <<' ' << y2 << '\n';

        for (int x = x1; x <= x2; x++) 
        {

            bm_data[y1][x].r = rect.color[0];
            bm_data[y1][x].g = rect.color[1];
            bm_data[y1][x].b = rect.color[2];
        }
        for (int y = y1; y >= y2; y--) 
        {

            bm_data[y][x1].r = rect.color[0];
            bm_data[y][x1].g = rect.color[1];
            bm_data[y][x1].b = rect.color[2];
        }
        for (int x = x1; x <= x2; x++) 
        {

            bm_data[y2][x].r = rect.color[0];
            bm_data[y2][x].g = rect.color[1];
            bm_data[y2][x].b = rect.color[2];
        }
        for (int y = y1; y >= y2; y--) 
        {

            bm_data[y][x2].r = rect.color[0];
            bm_data[y][x2].g = rect.color[1];
            bm_data[y][x2].b = rect.color[2];
        }
    }
    if (rect.fill == true)
    {
        x1++;
        y1--;
        x2--;
        y2++;
        for (int y = y1; y >= y2; y--)
        {
            for (int x = x1; x <= x2; x++)
            {
                bm_data[y][x].r = rect.fill_color[0];
                bm_data[y][x].g = rect.fill_color[1];
                bm_data[y][x].b = rect.fill_color[2];
            }
        }
    }
}



void Image::circle(Circle & circ)
{
    int x1, x2, y1, y2;
    int xc = circ.center[0];
    int yc = circ.center[1];
    for (int k = 0; k < circ.thickness; k++)
    {
        int x = 0;
        int r = circ.radius + k;
        int y = r;
        int d = 1 - 2 * r;
        int error = 0;

        while (y >= 0) {
            if (xc + x < bm_width && yc + y < bm_height && yc + y >= 0 && xc + x >= 0)
            {
                bm_data[yc + y][xc + x].r = circ.color[0];
                bm_data[yc + y][xc + x].g = circ.color[1];
                bm_data[yc + y][xc + x].b = circ.color[2];   
            }
            if (xc + x >= 0 && yc - y < bm_height && xc + x < bm_width && yc - y >= 0)
            {
                bm_data[yc - y][xc + x].r = circ.color[0];
                bm_data[yc - y][xc + x].g = circ.color[1];
                bm_data[yc - y][xc + x].b = circ.color[2];
            }
            if (xc - x < bm_width && yc + y >= 0 && yc + y < bm_height && xc - x >= 0)
            {
                bm_data[yc + y][xc - x].r = circ.color[0];
                bm_data[yc + y][xc - x].g = circ.color[1];
                bm_data[yc + y][xc - x].b = circ.color[2];
            }
            if (xc - x >= 0 && yc - y >= 0 && xc - x < bm_width && yc - y < bm_height)
            {
                bm_data[yc - y][xc - x].r = circ.color[0];
                bm_data[yc - y][xc - x].g = circ.color[1];
                bm_data[yc - y][xc - x].b = circ.color[2];
            }
            error = 2 * (d + y) - 1;
            if (d < 0 && error <= 0)
            {
                ++x;
                d += 2 * x + 1;
                continue;
            }
            if(d > 0 && error > 0) {
                --y;
                d += 1 - 2 * y;
                continue;
		    }
            ++x;
            d += 2 * (x - y);
            --y;
        }
        x1 = xc - r;
        x2 = xc + r;
        y1 = yc + r;
        y2 = yc - r;
    }
    for (int y = y1; y >= y2; y--)
    {
        for (int x = x1; x <= x2; x++)
        {
            double hyp = pow(pow(xc - x, 2.0) + pow(yc - y, 2), 0.5);
            if (x + 1 < bm_width && x - 1 >= 0 && y + 1 < bm_height && y - 1 >= 0 && bm_data[y][x].r != circ.color[0]
             && bm_data[y][x].g != circ.color[1] && bm_data[y][x].b != circ.color[2] && hyp >= circ.radius && 
             bm_data[y-1][x].r == circ.color[0] && bm_data[y-1][x].g == circ.color[1] && bm_data[y-1][x].b == circ.color[2]
             && bm_data[y+1][x].r == circ.color[0] && bm_data[y+1][x].g == circ.color[1] && bm_data[y+1][x].b == circ.color[2]
             && bm_data[y][x+1].r == circ.color[0] && bm_data[y][x+1].g == circ.color[1] && bm_data[y][x+1].b == circ.color[2]
             && bm_data[y][x-1].r == circ.color[0] && bm_data[y][x-1].g == circ.color[1] && bm_data[y][x-1].b == circ.color[2]) 
            {
                bm_data[y][x].r = circ.color[0];
                bm_data[y][x].g = circ.color[1];
                bm_data[y][x].b = circ.color[2];
            }
            else if (circ.fill == true && hyp < circ.radius && y < bm_height && y >= 0 && x < bm_width && x >= 0) {
                if (bm_data[y][x].r != circ.color[0] && bm_data[y][x].g != circ.color[1] && bm_data[y][x].b != circ.color[2])
                {
                    bm_data[y][x].r = circ.fill_color[0];
                    bm_data[y][x].g = circ.fill_color[1];
                    bm_data[y][x].b = circ.fill_color[2];
                }
            }
        }
    }
}



void Image::rotate (Rotate & rot) 
{
    rot.left_up[0] = rot.left_up[0] >= bm_width ? bm_width - 1 : rot.left_up[0];
    rot.left_up[1] = rot.left_up[1] >= bm_height ? bm_height - 1 : rot.left_up[1];
    rot.right_down[0] = rot.right_down[0] >= bm_width ? bm_width - 1 : rot.right_down[0];
    rot.right_down[1] = rot.right_down[1] >= bm_height ? bm_height - 1 : rot.right_down[1];
    if (rot.left_up[0] > rot.right_down[0])
    {
        int tmp = rot.left_up[0];
        rot.left_up[0] = rot.right_down[0];
        rot.right_down[0] = tmp;
    }
    if (rot.left_up[1] < rot.right_down[1])
    {
        int tmp = rot.left_up[1];
        rot.left_up[1] = rot.right_down[1];
        rot.right_down[1] = tmp;
    }
    int x1 = rot.left_up[0];
    int y1 = rot.left_up[1];
    int x2 = rot.right_down[0];
    int y2 = rot.right_down[1];

    int h = y1 - y2 + 1;
    int w = x2 - x1 + 1;

    std::cout << x1 << ' ' << x2 << ' ' << y1 <<' ' << y2 << std::endl;
    std::vector<std::vector<Color>> temp(w, std::vector<Color>(h));
    if (rot.angle == 90 || rot.angle == 270)
    {
        int xn = w >= h ? (w - h) / 2 + x1 : x1 - (h - w) / 2;
        int yn = w >= h ? (w - h) / 2 + y1 : y1 - (h - w) / 2;

        for (int i = 0; i < w; i++) 
        {
            for (int j = 0; j < h; j++)
            {
                if (y2 + j < bm_height && x1 + i < bm_width)
                {
                    temp[i][j] = bm_data[y2+j][x1+i];
                    // temp[i][j].r = 255;
                    // temp[i][j].g = 255;
                    // temp[i][j].b = 255;
                }
            }
        }
        std::cout << temp.size() << ' ' << temp[0].size() << std::endl;
        if (rot.angle == 90) 
        {
            for (int i = 0; i < w; i++) 
            {
                for (int j = 0; j < h; j++)
                {
                    
                    if (yn - i >= 0 && xn + j < bm_width && xn + j >= 0 && yn - i < bm_height)
                    {
                        bm_data[yn-i][xn+j] = temp[i][j];
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < w; i++) 
            {
                for (int j = 0; j < h; j++)
                {
                    
                    if (yn + i >= 0 && xn + j < bm_width && xn + j >= 0 && yn - i < bm_height)
                    {
                        bm_data[yn-i][xn+j] = temp[temp.size() - 1 - i][temp[i].size() - 1 - j];
                    }
                }
            }
        }
        
    }
    else if (rot.angle == 180)
    {
        for (int y = y1, ny = y2; y >= ny; y--, ny++)
        {
            for (int x = x1, nx = x2; x <= x2; x++, nx--)
            {
                if (y != ny || x < nx) 
                {
                    Color tmp = bm_data[ny][nx];
                    bm_data[ny][nx] = bm_data[y][x];
                    bm_data[y][x] = tmp;
                }
                else
                {
                    break;
                }
            }
        }
    }
    
}


void Image::ornament(Ornament & orn)
{
    if (orn.pattern == "circle")
    {
        double xc = bm_width / 2 - 1;
        double yc = bm_height / 2 - 1;
        double rad = yc > xc ? xc + 1 : yc + 1;

        std::cout << xc << ' ' << yc << std::endl;
        std::array<double, 2> center{xc, yc};
        for (int y = 0; y < bm_height; y++)
        {
            for (int x = 0; x < bm_width; x++) 
            {
                double hyp = pow(pow(center[0] - x, 2.0) + pow(center[1] - y, 2.0), 0.5);
                if (hyp > rad)
                {
                    bm_data[y][x].r = orn.color[0];
                    bm_data[y][x].g = orn.color[1];
                    bm_data[y][x].b = orn.color[2];
                }
            }
        }
    }
    else if (orn.pattern == "rectangle")
    {
        std::cout << bm_height;
        Rectangle rect{{0, static_cast<int>(bm_height - 1)}, {static_cast<int>(bm_width - 1), 0}, orn.thickness, orn.color, false};
        for (int k = 0; k < orn.count; k++)
        {
            rectangle(rect);
            rect.left_up[0] += 2 * orn.thickness;
            rect.left_up[1] -= 2 * orn.thickness;
            rect.right_down[0] -= 2 * orn.thickness;
            rect.right_down[1] += 2 * orn.thickness;
            if (rect.left_up[1] < 0 || rect.right_down[0] < 0)
            {
                std::cerr << "Oops, to match rectangles, but it's ok" << std::endl;
                break;
            }
        }
    }

    else if (orn.pattern == "semicircles")
    {
        int wd = bm_width / orn.count;
        int hd = bm_height / orn.count;
        Circle circ({wd / 2, static_cast<int>(bm_height - 1)}, wd / 2, orn.thickness, orn.color, false, {0,0,0});
        // std::cout << circ.center[0] << ' ' << circ.center[1];
        for (int k = 0; k < orn.count; k++) 
        {
            circle(circ);
            circ.center[0] += wd;
            std::cout << circ.center[0] << std::endl;
            
        }
        circ.center = {wd / 2, 0};
        for (int k = 0; k < orn.count; k++) 
        {
            circle(circ);
            circ.center[0] += wd;
        }
        circ.center = {0, static_cast<int>(bm_height - hd / 2)};
        circ.radius = hd / 2;
        for (int k = 0; k < orn.count; k++) 
        {
            circle(circ);
            circ.center[1] -= hd;
        }
        circ.center = {static_cast<int>(bm_width - 1), static_cast<int>(bm_height - 1) - hd / 2};
        for (int k = 0; k < orn.count; k++) 
        {
            circle(circ);
            circ.center[1] -= hd;
        }
    }
}

