#include "stdafx.h"
#include "mainGame.h"

//객체지향적 코딩으로 넘어오면서
//한개의 헤더파일은 여러개의 cpp를 거느릴수 있다
//프로젝트의 코딩량이 많아지면 함수 하나에 처리되는 양이 커져서
//코드를 알아보기 힘들어지는데
//요렇게 헤더파일에서 함수를 선언하고
//각 함수에 맞는 cpp파일을 따로 빼서 만들면
//렌더전용 cpp, update전용 cpp, 충돌전용 cpp
//관리하기가 편해진다

void mainGame::collision()
{
	
	for (int i = 0; i < _ship->getDaepodong()->getVBullet().size(); i++)
	{
		for (int j = 0; j < _enemyManager->getVMinion().size(); j++)
		{
			//충돌했다면? 스페이스 쉽에서 미사일을 지워주는 함수에 인자값을 넘겨주고
			//여기서 직접적으로 지워줄순 있는데 그렇게 하지 않음
			//이유는 다른 곳에서 참조되고 있을 수도 있기때문에
			//여기서 직접적으로 지워버리면 그 미사일에 영향이 갈수도 있기 때문에
			//지우는 건 그 객체가 담당하고
			//여기서는 지우라고 통보만 해준다


			_ship->removeMissile(i);
			_enemyManager->removeMinion(j);
			break;
		}
	}


}