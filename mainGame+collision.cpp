#include "stdafx.h"
#include "mainGame.h"

//��ü������ �ڵ����� �Ѿ���鼭
//�Ѱ��� ��������� �������� cpp�� �Ŵ����� �ִ�
//������Ʈ�� �ڵ����� �������� �Լ� �ϳ��� ó���Ǵ� ���� Ŀ����
//�ڵ带 �˾ƺ��� ��������µ�
//�䷸�� ������Ͽ��� �Լ��� �����ϰ�
//�� �Լ��� �´� cpp������ ���� ���� �����
//�������� cpp, update���� cpp, �浹���� cpp
//�����ϱⰡ ��������

void mainGame::collision()
{
	
	for (int i = 0; i < _ship->getDaepodong()->getVBullet().size(); i++)
	{
		for (int j = 0; j < _enemyManager->getVMinion().size(); j++)
		{
			//�浹�ߴٸ�? �����̽� ������ �̻����� �����ִ� �Լ��� ���ڰ��� �Ѱ��ְ�
			//���⼭ ���������� �����ټ� �ִµ� �׷��� ���� ����
			//������ �ٸ� ������ �����ǰ� ���� ���� �ֱ⶧����
			//���⼭ ���������� ���������� �� �̻��Ͽ� ������ ������ �ֱ� ������
			//����� �� �� ��ü�� ����ϰ�
			//���⼭�� ������ �뺸�� ���ش�


			_ship->removeMissile(i);
			_enemyManager->removeMinion(j);
			break;
		}
	}


}