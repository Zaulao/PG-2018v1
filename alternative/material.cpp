
class Material{
    private:
        double ke;
        double kd;
        double ks;
        double alpha;
        Vec3 <double> color;

    public:
        Material(double ke, double kd, double ks, double alpha, Vec3 <double> color){
            this->ke = ke;
            this->kd = kd;
            this->ks = ks;
            this->alpha = alpha;
            this->color = color;
        }

        Vec3 <double> getColor(){
            return this->color;
        }

        double getKe(){
            return this->ke;
        }

        double getKs(){
            return this->ks;
        }

        double getKd(){
            return this->kd;
        }

        double getAlpha(){
            return this->alpha;
        }

};