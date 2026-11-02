#include <iostream>
#include <cmath>

// Electric_Field: 3D electric field stored in a dynamic array
class Electric_Field
{
  private:
    double *E;
  public:
    // Default field 
    Electric_Field()
    {
        E = new double[3];
        E[0] = E[1] = E[2] = 0.0;
    }

    // Constructor takes three components
    Electric_Field(double x, double y, double z)
    {
        E = new double[3];
        E[0] = x;
        E[1] = y;
        E[2] = z;
    }

    // Copy constructor 
    Electric_Field(const Electric_Field &other)
    {
        E = new double[3];
        for (int i = 0; i < 3; i++) E[i] = other.E[i];
    }

    // Copy assignment 
    Electric_Field &operator=(const Electric_Field &other)
    {
        if (this != &other)
            for (int i = 0; i < 3; i++) E[i] = other.E[i];
        return *this;
    }

    // Destructor
    ~Electric_Field()
    {
        delete[] E;
    }

    // Getters
    double getX() const { return E[0]; }
    double getY() const { return E[1]; }
    double getZ() const { return E[2]; }

    // Setters
    void setX(double x) { E[0] = x; }
    void setY(double y) { E[1] = y; }
    void setZ(double z) { E[2] = z; }
    void setComponents(double x, double y, double z)
    {
        E[0] = x;
        E[1] = y;
        E[2] = z;
    }

    // Magnitude of the vector
    double calculateMagnitude() const
    {
        return std::sqrt(E[0] * E[0] + E[1] * E[1] + E[2] * E[2]);
    }

    // Inner product of the field with itself
    double innerProduct() const
    {
        return E[0] * E[0] + E[1] * E[1] + E[2] * E[2];
    }

    // Inner product of this field with anothers
    double innerProduct(const Electric_Field &other) const
    {
        return E[0] * other.E[0] + E[1] * other.E[1] + E[2] * other.E[2];
    }
};


// Magnetic_Field: 3D magnetic field stored in a dynamic array
class Magnetic_Field
{
  private:
    double *B;

  public:
    // Default constructor: field of zeros
    Magnetic_Field()
    {
        B = new double[3];
        B[0] = B[1] = B[2] = 0.0;
    }

    // Constructor taking the three components
    Magnetic_Field(double x, double y, double z)
    {
        B = new double[3];
        B[0] = x;
        B[1] = y;
        B[2] = z;
    }

    // Copy constructor 
    Magnetic_Field(const Magnetic_Field &other)
    {
        B = new double[3];
        for (int i = 0; i < 3; i++) B[i] = other.B[i];
    }

    // Copy assignment 
    Magnetic_Field &operator=(const Magnetic_Field &other)
    {
        if (this != &other)
            for (int i = 0; i < 3; i++) B[i] = other.B[i];
        return *this;
    }

    // Destructor
    ~Magnetic_Field()
    {
        delete[] B;
    }

    // Getters
    double getX() const { return B[0]; }
    double getY() const { return B[1]; }
    double getZ() const { return B[2]; }

    // Setters
    void setX(double x) { B[0] = x; }
    void setY(double y) { B[1] = y; }
    void setZ(double z) { B[2] = z; }
    void setComponents(double x, double y, double z)
    {
        B[0] = x;
        B[1] = y;
        B[2] = z;
    }

    // Magnitude of the vector
    double calculateMagnitude() const
    {
        return std::sqrt(B[0] * B[0] + B[1] * B[1] + B[2] * B[2]);
    }

    // Unit vector in the direction of the field.
    // Returned as a Magnetic_Field whose magnitude is 1
    Magnetic_Field calculateUnitVector() const
    {
        double mag = calculateMagnitude();
        if (mag == 0.0)
            return Magnetic_Field(0.0, 0.0, 0.0);
        return Magnetic_Field(B[0] / mag, B[1] / mag, B[2] / mag);
    }
};

int main()
{
    // Electric fields 
    Electric_Field E_default;                    
    Electric_Field E_components(1e5, 10.9, 1.7e2); 
    Electric_Field E_setter;                     
    E_setter.setX(3.0);
    E_setter.setY(4.0);
    E_setter.setZ(12.0);

    std::cout << "===== Electric Fields =====\n";
    std::cout << "E_default    = (" << E_default.getX() << ", " << E_default.getY()
              << ", " << E_default.getZ() << ")\n";
    std::cout << "  Magnitude     : " << E_default.calculateMagnitude() << "\n";
    std::cout << "  Inner product : " << E_default.innerProduct() << "\n\n";

    std::cout << "E_components = (" << E_components.getX() << ", " << E_components.getY()
              << ", " << E_components.getZ() << ")\n";
    std::cout << "  Magnitude     : " << E_components.calculateMagnitude() << "\n";
    std::cout << "  Inner product : " << E_components.innerProduct() << "\n\n";

    std::cout << "E_setter     = (" << E_setter.getX() << ", " << E_setter.getY()
              << ", " << E_setter.getZ() << ")\n";
    std::cout << "  Magnitude     : " << E_setter.calculateMagnitude() << "\n";
    std::cout << "  Inner product : " << E_setter.innerProduct() << "\n\n";

    //  Magnetic fields
    Magnetic_Field B_default;                    
    Magnetic_Field B_components(2.5e-3, 1.2e-3, 4.0e-3); 
    Magnetic_Field B_setter;                     
    B_setter.setX(1.0);
    B_setter.setY(2.0);
    B_setter.setZ(2.0);

    std::cout << "===== Magnetic Fields =====\n";

    Magnetic_Field *fields[3] = {&B_default, &B_components, &B_setter};
    const char *names[3] = {"B_default   ", "B_components", "B_setter    "};

    for (int i = 0; i < 3; i++)
    {
        Magnetic_Field unit = fields[i]->calculateUnitVector();
        std::cout << names[i] << " = (" << fields[i]->getX() << ", "
                  << fields[i]->getY() << ", " << fields[i]->getZ() << ")\n";
        std::cout << "  Magnitude   : " << fields[i]->calculateMagnitude() << "\n";
        std::cout << "  Unit vector : (" << unit.getX() << ", " << unit.getY()
                  << ", " << unit.getZ() << ")\n\n";
    }

    return 0;
}