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
    std::string name, path, name1, name2, colorspace, type, out, in, kernel;
    int wys, szer, x, y, x1, y1, x2, y2, x3, y3, x4, y4, scale, rad;
    float r, g, b, weight, val;

	  if (command=="exit") {
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
			line >> name >> colorspace;
			line >> r >> g >> b;
			op.fill(name, colorspace, r, g, b);
		}
		else if(command=="get"){
			line >> name >> x >> y; // >> colorspace;
			op.get(name, x, y);
			//op.get(name, x, y, colorspace);
		}
		else if(command=="put"){
			line >> name >> x >> y >> colorspace;
			line >> r >> g >> b;
			op.put(name, x, y, colorspace, r, g, b);
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
      op.line(name, x1, y1, x2, y2);
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
    } else if(command=="triangle") {
      line >> name >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
      op.AddTriangle(name, x1, y1, x2, y2, x3, y3);
    }
		else {
	    std::cout << "Unknown command " << command << std::endl;
	  }
  }
  return 0;
}
