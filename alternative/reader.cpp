#include <fstream>
#include <map>

class Reader {
    private: 
        fstream reader;
        string s;

    public: 
        map <string, double> res;
        map <string, double> camera;
        map <string, double> material;
        map <string, double> objetos;
      

        Reader(map<string, double> res, map<string, double> camera, map<string, double> material, map<string, double> objetos){
            this->res = res;
            this->camera = camera;
            this->material = material;
            this->objetos = objetos;
        }

        Reader *read_file(){
            string s;
            int count = 0;
            fstream reader;
            reader.open("file.txt");
            reader >> s;
            while(reader.good()){
                reader >> s;
                if(s == "#resolução"){
                    //2 e 3
                    reader >> s;
                    for(int i = 2; i <=3; i++){
                        reader >> s;
                        switch(i){
                            case 2:
                                this->res["w"] = atof(s.c_str());
                                break;
                            case 3:
                                this->res["h"] = atof(s.c_str());
                                break;
                        }       
                    }
                }else if(s == "#câmera"){
                    // 2 a 12
                    reader >> s;
                    for(int i = 2; i <= 12; i++){
                        reader >> s;
                        switch(i){
                            case 2:
                                this->camera["px"] = atof(s.c_str());
                                break;
                            case 3:
                                this->camera["py"] = atof(s.c_str());
                                break;
                            case 4:
                                this->camera["pz"] = atof(s.c_str());
                                break;
                            case 5:
                                this->camera["tx"] = atof(s.c_str());
                                break;
                            case 6:
                                this->camera["tz"] = atof(s.c_str());
                                break;
                            case 8:
                                this->camera["ux"] = atof(s.c_str());
                                break;
                            case 9:
                                this->camera["uy"] = atof(s.c_str());
                                break;
                            case 10:
                                this->camera["uz"] = atof(s.c_str());
                                break;
                            case 11:
                                this->camera["fov"] = atof(s.c_str());
                                break;
                            case 12:
                                this->camera["f"] = atof(s.c_str());
                                break;

                        }
                    }
                }else if(s == "#materiais" || s == "material"){
                    //2 a 8
                    if(s != "material") reader >> s;
                    string material_name;
                    for(int i = 2; i <= 9; i++){
                        reader >> s;
                        switch(i){
                            case 2: 
                                material_name = s;
                                break;
                            case 3:
                                this->material[material_name+"_r"] = atof(s.c_str()); 
                                break;
                            case 4:
                                this->material[material_name+"_g"] = atof(s.c_str()); 
                                break;
                            case 5:
                                this->material[material_name+"_b"] = atof(s.c_str()); 
                                break;
                            case 6:
                                this->material[material_name+"_kd"] = atof(s.c_str()); 
                                break;
                            case 7:
                                this->material[material_name+"_ks"] = atof(s.c_str()); 
                                break;
                            case 8:
                                this->material[material_name+"_ke"] = atof(s.c_str()); 
                                break;
                            case 9:
                                this->material[material_name+"_alpha"] = atof(s.c_str());
                        }
                    }
                }else if(s == "#objetos" || s == "sphere"){
                    //2 a 6
                    if(s == "sphere") count++;
                    else reader >> s;
                    string material_name_obj;
                    for(int i = 2; i <= 6; i++){
                        reader >> s;
                        switch(i){
                            case 2:
                                this->objetos["sphere"+to_string(count)+"_cx"] = atof(s.c_str());
                                break;
                            case 3:
                                this->objetos["sphere"+to_string(count)+"_cy"] = atof(s.c_str());
                                break;
                            case 4:
                                this->objetos["sphere"+to_string(count)+"_cz"] = atof(s.c_str());
                                break;
                            case 5:
                                this->objetos["sphere"+to_string(count)+"_r"] = atof(s.c_str());
                                break;
                            case 6:
                                material_name_obj = s;
                                break;
                        }
                    }

                }
            }    
            return this;              
        }
};
