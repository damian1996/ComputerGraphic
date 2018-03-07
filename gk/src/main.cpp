#include "image.h"
#include "clipwindow.h"
#include "operations.h"
#include <iostream>
#include <sstream>
#include <map>
#include <string>

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
		//a wywoływało się mapka[i](line);

	  if (command=="exit") {
	    int code;
	    line >> code;
	    std::cout << "Exiting with code " << code << std::endl;
	    return code;
	  }
	  else if(command=="load"){
			std::string path, name;
			line >> path;
			line >> name;
			op.load(path, name);
	  	}
		else if(command=="save"){
			std::string path, name;
			line >> path;
			line >> name;
			op.save(path, name);
		}
		else if(command=="create"){
			std::string name;
			int wys, szer;
			line >> name;
			line >> szer;
			line >> wys;
			op.create(name, szer, wys);
		}
		else if(command=="fill"){
			std::string name, colorspace;
			float r, g, b;
			line >> name;
			line >> colorspace;
			line >> r >> g >> b;
			op.fill(name, colorspace, r, g, b);
		}
		else if(command=="get"){
			std::string name;
			int x, y;
			line >> name;
			line >> x >> y;
			op.get(name, x, y);
		}
		else if(command=="put"){
			std::string name, colorspace;
			int x, y;
			float r, g, b;
			line >> name;
			line >> x >> y;
			line >> colorspace;
			line >> r >> g >> b;
			op.put(name, x, y, colorspace, r, g, b);
		}
		else if(command=="noclip"){
			std::string name;
			line >> name;
			op.noclip(name);
		}
		else if(command=="clip"){
			std::string name;
			int x1, y1, x2, y2;
			line >> name;
			line >> x1 >> y1 >> x2 >> y2;
			op.clip(name, x1, y1, x2, y2);
		}
		else {
	      std::cout << "Unknown command " << command << std::endl;
	    }
  }
  return 0;
}
