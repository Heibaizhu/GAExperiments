#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <functional>
#include <math.h>

using std::vector;

namespace GA
{
	typedef vector<double> CHROM;
	const double MIN_VAL = -1e300;

	double Rand01();

	double RandRange(double lb, double ub);

	//�Ŵ�������
	class CIndividual
	{
	public:
		//���캯��
		CIndividual() : m_dFitValue(0.0), m_vecdChrom() {};
		//Ⱦɫ��
		CHROM m_vecdChrom;
		//��Ӧֵ
		double m_dFitValue;
	};

	namespace NaiveGA
	{
		//����������
		class CEvolution
		{
		protected:
			static bool _Criterion(const CIndividual& ind1, const CIndividual& ind2)
			{
				return ind1.m_dFitValue > ind2.m_dFitValue;	// ��������
			}
			inline void _Sort()
			{
				std::sort(m_veciPopulation.begin(), m_veciPopulation.end(), _Criterion);
			}

		public:
			vector <CIndividual> m_veciPopulation;	// ��Ⱥ
			int m_nCurrGen;	// ��ǰ����
			int m_nGenerations;	// �ܴ���
			double(*m_fcnObj)(CIndividual&);	// Ŀ�꺯��
			int m_nPopSize;	// ��Ⱥ��С
			int m_nGenes;	// ÿ��Ⱦɫ���ϻ�����
			double m_dPr;	// ��ֳ����
			double m_dPc;	// �ӽ�����
			vector<double> m_vecdLB;	// ��Ԫȡֵ�½�
			vector<double> m_vecdUB;	// ��Ԫȡֵ�Ͻ�
			vector<std::function<double(CHROM&)>>  m_fcnConstraints;	// Լ������

		public:
			//���캯�������ó�ʼ������
			CEvolution(double(*) (CIndividual&), int, int, int, vector<double>&&, vector<double>&&, double, double);
			//������һ��
			void NextGeneration();
			//��ʼ����Ⱥ
			void Init();
			// �Ŵ�����
			// ��ֳ����
			virtual void Reproduce();
			// ��������
			virtual void Cross();
			// ��������
			virtual void Mutate();
			// ѡ����
			virtual const CIndividual& Select() const;
			// ��Ӧֵ����
			virtual double CalcFitness(CIndividual& ind)
			{
				double dTarVal = this->m_fcnObj(ind);
				for (auto i = 0; i < m_nGenes; i++)
				{
					// ���ÿһ��������ȡֵ��Χ
					if ((ind.m_vecdChrom[i] - m_vecdLB[i]) * (m_vecdUB[i] - ind.m_vecdChrom[i]) < 0)
						return MIN_VAL;
				}

				for (auto fun : this->m_fcnConstraints)
				{
					if (fun(ind.m_vecdChrom) < 0)
						return MIN_VAL;
				}
				return dTarVal;
			}
		};
	}

}