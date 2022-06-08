#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include "cmath"

namespace mt::math{
    // MY_DEBUG
    #define MY_DEBUG

    template<typename T, int N, int M>
    struct MasWrapper{
        T mas[N][M];
    };

    template<typename T, int N, int M>
    class Matrix {
    public:
        Matrix() {
#ifdef MY_DEBUG
            std::cout << "Constructor" << std::endl;
#endif
            m_n = N;
            m_m = M;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = 0;
        }

        Matrix(const T mas[N][M]) {
#ifdef MY_DEBUG
            std::cout << "Constructor" << std::endl;
#endif
            m_n = N;
            m_m = M;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = mas[i][j];
        }

        Matrix(const MasWrapper<T, N, M> &mas) {
#ifdef MY_DEBUG
            std::cout << "Constructor" << std::endl;
#endif
            m_n = N;
            m_m = M;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = mas.mas[i][j];
        }
        Matrix(double matrix[9]){
#ifdef MY_DEBUG
            std::cout << "Constructor" << std::endl;
#endif
            m_n = 3;
            m_m = 3;
            for (int i = 0; i < m_n; i++) {
                for (int j = 0; j < m_m; j++) {
                    std::cout << matrix[i * 3 + j] << " ";
                    m_mat[i][j] = matrix[i * 3 + j];
                }
            }
//            for (int i = 0; i < m_n; i++)
//                for (int j = 0; j < m_m; j++)
//                   std::cout << m_mat[i][j] << std::endl;

        }

        Matrix(const Matrix<T, N, M> &mat) {
#ifdef MY_DEBUG
            std::cout << "Copy constructor" << std::endl;
#endif

            m_n = mat.m_n;
            m_m = mat.m_m;

            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = mat.m_mat[i][j];
        }

        int getN() const { return m_n; }

        int getM() const { return m_m; }

        T get(int i, int j) const { return m_mat[i][j]; }

        void set(int i, int j, T data) { m_mat[i][j] = data; }

        template<typename A, int B, int C>
        Matrix<T, N, M> &operator=(const Matrix<A, B, C> &mat) {
#ifdef MY_DEBUG
            std::cout << "Operator =" << std::endl;
#endif

            m_n = mat.getN();
            m_m = mat.getM();

            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    m_mat[i][j] = mat.get(i, j);

            return *this;
        }

        template<typename A, int B, int C>
        Matrix<T, N, M> operator+(const Matrix<A, B, C> &mat) {
#ifdef MY_DEBUG
            std::cout << "operator+" << std::endl;
#endif
            Matrix<T, N, M> tmp;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
            return tmp;
        }

        template<typename A, int B, int C>
        Matrix<T, N, M> operator-(const Matrix<A, B, C> &mat) {
#ifdef MY_DEBUG
            std::cout << "operator-" << std::endl;
#endif
            Matrix<T, N, M> tmp;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < m_m; j++)
                    tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
            return tmp;
        }

        template<typename A, int B, int C>
        Matrix<T, N, C> operator*(const Matrix<A, B, C> &mat) {
#ifdef MY_DEBUG
            std::cout << "operator*" << std::endl;
#endif
            Matrix<T, N, C> tmp;
            for (int i = 0; i < m_n; i++)
                for (int j = 0; j < mat.getM(); j++) {
                    T sum = 0;
                    for (int k = 0; k < m_m; k++)
                        sum += m_mat[i][k] * mat.get(k, j);
                    tmp.set(i, j, sum);
                }

            return tmp;
        }

        float Determinant() {
            float determinant = 0;
            if (m_n == 1 && m_m == 1) {
                determinant = m_mat[0][0];
                return determinant;
            } else if (m_n == 2 && m_m == 2) {
                determinant = m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
                return determinant;
            } else if (m_n == 3 && m_m == 3) {
                determinant = m_mat[0][0] * m_mat[1][1] * m_mat[2][2] + m_mat[0][1] * m_mat[1][2] * m_mat[2][0]
                              + m_mat[0][2] * m_mat[1][0] * m_mat[2][1] - m_mat[0][2] * m_mat[1][1] * m_mat[2][0]
                              - m_mat[0][0] * m_mat[1][2] * m_mat[2][1] - m_mat[0][1] * m_mat[1][0] * m_mat[2][2];
                return determinant;
            } else {
                std::cout << "Операция не поддерживается" << std::endl;
                return -1;
            }
        }

        Matrix Inverse(){
            Matrix<T, N, M> tmp;
            for(int i = 0; i < m_n; i++)
                for(int j = 0; j < m_m; j++)
                    tmp.m_mat[i][j] = 0;
            if((m_n == 2 && m_m == 2) || (m_n == 3 && m_m == 3)){
                T det = Determinant();
                std::cout << det << std::endl;
                if(det == 0) {
                    std::cout << "Обратной матрицы не существует, так как определитель равен 0" << std::endl;
                    return tmp;
                }
                if(m_n == 2){
                    tmp.m_mat[0][0] = m_mat[1][1]/det;
                    tmp.m_mat[0][1] = -m_mat[0][1]/det;
                    tmp.m_mat[1][0] = -m_mat[1][0]/det;
                    tmp.m_mat[1][1] = m_mat[0][0]/det;
                }
                if(m_n == 3){
                    tmp.m_mat[0][0] = (m_mat[1][1]*m_mat[2][2] - m_mat[2][1]*m_mat[1][2])/det;
                    tmp.m_mat[0][1] = -(m_mat[0][1]*m_mat[2][2] - m_mat[2][1]*m_mat[0][2])/det;
                    tmp.m_mat[0][2] = (m_mat[0][1]*m_mat[1][2] - m_mat[1][1]*m_mat[0][2])/det;
                    tmp.m_mat[1][0] = -(m_mat[1][0]*m_mat[2][2] - m_mat[2][0]*m_mat[1][2])/det;
                    tmp.m_mat[1][1] = (m_mat[0][0]*m_mat[2][2] - m_mat[2][0]*m_mat[0][2])/det;
                    tmp.m_mat[1][2] = -(m_mat[0][0]*m_mat[1][2] - m_mat[1][0]*m_mat[0][2])/det;
                    tmp.m_mat[2][0] = (m_mat[1][0]*m_mat[2][1] - m_mat[2][0]*m_mat[1][1])/det;
                    tmp.m_mat[2][1] = -(m_mat[0][0]*m_mat[2][1] - m_mat[2][0]*m_mat[0][1])/det;
                    tmp.m_mat[2][2] = (m_mat[0][0]*m_mat[1][1] - m_mat[1][0]*m_mat[0][1])/det;
                }
            } else {
                std::cout << "Вычисление обратной матрицы такого порядка не поддерживается" << std::endl;
            }
            return tmp;
        }

        std::string Transform_to_str(std::string result){
            std::string str, s;
            for (int i = 0; i < m_n; i++) {
                for (int j = 0; j < m_m; j++) {
                    //std::cout << m_mat[i][j] << std::endl;
                    str = std::to_string(std::round(m_mat[i][j]*1000)/1000);
                    for (int q = 0; q < str.size(); q++){
                        if (str.size() - q > 3){
                            s += str[q];
                        }
                    }
                    result += s + " ";
                    s = "";
                }
                result += "\n";
            }
            //std::cout << result << std::endl;
            return result;
        }

        Matrix Transposed() {
            Matrix<T, N, M> tmp;
            for (int i = 0; i < m_n; i++) {
                for (int j = 0; j < m_m; j++) {
                    tmp.m_mat[j][i] = m_mat[i][j];
                }
            }
            return tmp;
    }

        ~Matrix(){
#ifdef MY_DEBUG
            std::cout << "Destructor" << std::endl;
#endif
        }

        template<typename A, int B, int C>
        friend std::istream& operator>>(std::istream& os, Matrix<A, B, C>& mat);

        template<typename A, int B, int C>
        friend std::ostream& operator<<(std::ostream& os, const Matrix<A, B, C>& mat);


    private:
        int m_n, m_m;
        T m_mat[N][M];
    };


    template<typename T, int N, int M>
    std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat){
        for (int i = 0; i < mat.m_n; i++)
            for (int j = 0; j < mat.m_m; j++)
                in >> mat.m_mat[i][j];
        return in;
    }

    template<typename T, int N, int M>
    std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat){
        out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
        for (int i = 0; i < mat.m_n; i++) {
            for (int j = 0; j < mat.m_m; j++)
                out << mat.m_mat[i][j] << " ";
            out << std::endl;
        }
        return out;
    }

    using Vec2i = Matrix<int, 2, 1>;
    using Vec2d = Matrix<double, 2, 1>;
    using Vec22i = Matrix<int, 2, 2>;
    using Vec22d = Matrix<double, 2, 2>;
    using Vec3d = Matrix<double, 3, 1>;
    using Vec33d = Matrix<double, 3, 3>;
}