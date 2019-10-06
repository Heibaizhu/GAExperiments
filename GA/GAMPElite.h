#pragma once
#include "GAMP.h"

namespace GA
{
	namespace GAMPElite
	{
		// �ุ���ӽ��ݻ��㷨
		class CEvolutionMPE: public GAMP::CEvolutionMP
		{
		protected:
			void _SelectParents(vector<CIndividual const*>&);
		public:
			int m_nCandidates = 2;	// ���ӿռ���ѡȡ�ĵ�����>=2
			int m_nElites = 2;	// ÿ�β����ӽ��ľ�Ӣ������
		public:
			CEvolutionMPE(
				double(*objfunc)(CIndividual&), int n,
				int np, int nc,
				vector<double>&& lb, vector<double>&& ub,
				double pr, double pc
			) :
				CEvolutionMP(objfunc, n, np, nc, std::move(lb), std::move(ub), pr, pc)
			{}

			CEvolutionMPE(
				double(*objfunc)(CIndividual&), int n,
				int np, int nc,
				vector<double>&& lb, vector<double>&& ub,
				double pr, double pc,
				double m
			) :
				CEvolutionMP(objfunc, n, np, nc, std::move(lb), std::move(ub), pr, pc, m)
			{}

			CEvolutionMPE(
				double(*objfunc)(CIndividual&), int n,
				int np, int nc,
				vector<double>&& lb, vector<double>&& ub,
				double pr, double pc,
				double m, double k, double l
			) :
				CEvolutionMP(objfunc, n, np, nc, std::move(lb), std::move(ub), pr, pc, m), 
				m_nElites(k), m_nCandidates(l)
			{}

			void Cross();
		};
	}
}