#include "image.h"
#include "clipwindow.h"
#include "operations.h"
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <cstring>
#include <vector>
#include "kernel.h"

int main(int argv, char** argc) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout << "Program GK" << std::endl;
  std::string lines, command;
  std::vector<std::string> v;
  Operations op;
  while (true) {

    std::getline(std::cin, lines);
    std::stringstream line(lines);
    line >> command;
    //pair<string, void(*)(stringstream&)> mapka[];
		//a wywolywalo się mapka[i](line);
    std::string name, path, name1, name2, colorspace, type, out, in, kernel, pen, affine;
    std::string namePolygon;
    int wys, szer, x, y, x1, y1, x2, y2, x3, y3, x4, y4, scale, rad, n;
    float r, g, b, weight, val, tx, ty;
    double angle;
    if(command=="")
      continue;
	  else if(command=="polygon") {
      std::vector<std::pair<int, int>> vertices;
      line >> name >> pen >> n;
      vertices.reserve(n);
      for(int i=0; i<n; i++) {
        //std::getline(std::cin, lines);
        //std::stringstream line(lines);
        std::cin >> x >> y;
        vertices.push_back(std::make_pair(x, y));
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      op.polygon(name, pen, n, vertices);
    }
    else if (command=="exit") {
	    int code;
	    line >> code;
	    std::cout << "Exiting with code " << code << std::endl;
	    return code;
	  }
	  else if(command=="load"){
			line >> path >> name;
			op.load(path, name);
	  }
		else if(command=="save"){
			line >> name >> path;
			op.save(name, path);
		}
		else if(command=="create"){
			line >> name >> szer >> wys;
			op.create(name, szer, wys);
		}
		else if(command=="fill"){
			line >> name; // >> colorspace;
			line >> r >> g >> b;
			//op.fill(name, colorspace, r, g, b);
			op.fill(name, r, g, b);
		}
		else if(command=="get"){
			line >> name >> x >> y; // >> colorspace;
			op.get(name, x, y);
			//op.get(name, x, y, colorspace);
		}
		else if(command=="put"){
      line >> name >> x >> y;
      //line >> name >> x >> y >> colorspace;
			line >> r >> g >> b;
			//op.put(name, x, y, colorspace, r, g, b);
			op.put(name, x, y, r, g, b);
		}
		else if(command=="noclip"){
			line >> name;
			op.noclip(name);
		}
		else if(command=="clip"){
			line >> name >> x1 >> y1 >> x2 >> y2;
			op.clip(name, x1, y1, x2, y2);
		}
    else if(command=="shrink") {
      line >> name >> scale;
      op.shrink(name, scale);
    }
    else if(command=="merge") {
      line >> name1 >> name2 >> weight;
      op.merge(name1, name2, weight);
    }
    else if(command=="colorsplit") {
      line >> name >> type;
      op.colorsplit(name, type);
    }
    else if(command=="compare") {
      line >> name1 >> name2;
      op.compare(name1, name2);
    }
    else if(command=="kernel") {
      std::vector<float> vec;
      line >> name >> x >> y;
      for(int i=0; i<y; i++) {
        std::getline(std::cin, lines);
        std::stringstream line(lines);
        for(int j=0; j<x; j++) {
          line >> val;
          vec.push_back(val);
        }
      }
      Kernel *k = new Kernel(x, y);
      k->fill(vec);
      vec.clear();
      op.kernel(name, k);
    }
    else if(command=="gamma") {
      line >> out >> name >> val;
      op.gamma(out, name, val);
    }
    else if(command=="convolveimg") {
      line >> out >> in >> kernel;
      op.convolveimg(out, in, kernel);
    }
    else if(command=="haar") {
      line >> in >> out;
      op.haar(in, out);
    }
    else if(command=="line") {
      line >> name >> x1 >> y1 >> x2 >> y2;
      //op.line(name, x1, y1, x2, y2, "P");
    }
    else if(command=="circle") {
      line >> name >> x >> y >> rad;
      op.circle(name, x, y, rad);
    }
    else if(command=="bezier") {
      line >> name >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
      op.bezier(name, x1, y1, x2, y2, x3, y3, x4, y4);
    }
    else if(command=="section") {
      line >> name >> x1 >> y1 >> x2 >> y2;
      op.AddSection(name, x1, y1, x2, y2);
    }
    else if(command=="triangle") {
      line >> name >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
      op.AddTriangle(name, x1, y1, x2, y2, x3, y3);
    }
    else if(command=="fft") {
      line >> name >> out;
      op.fft(name, out);
    }
    else if(command=="ifft") {
      line >> name >> out;
      op.ifft(name, out);
    }
    else if(command=="pen") {
      line >> type >> name >> r >> g >> b;
      op.addPen(name, r, g, b);
    }
    else if(command=="polygonobj") {
        line >> name >> n;
        std::vector<std::pair<double, double>> vertices;
        vertices.reserve(n);
        for(int i=0; i<n; i++) {
            std::cin >> x >> y;
            vertices.push_back(std::make_pair(x, y));
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        op.polygonobj(name, n, vertices);
    }
    else if(command=="draw") {
      line >> name >> pen >> namePolygon;
      op.draw(name, pen, namePolygon);
    }
    else if(command=="translate") {
      line >> name >> tx >> ty;
      op.translate(name, tx, ty);
    }
    else if(command=="scale") {
      line >> name >> tx >> ty;
      op.scale(name, tx, ty);
    }
    else if(command=="shear") {
      line >> name >> tx >> ty;
      op.shear(name, tx, ty);
    }
    else if(command=="rotate") {
      line >> name >> angle;
      op.rotate(name, angle);
    }
    else if(command=="transform") {
      line >> name1 >> affine >> name2;
      op.transform(name1, affine, name2);
    }
		else {
	    std::cout << "Unknown command " << command << std::endl;
	  }
  }
  return 0;
}
