#include "Framework.h"
#include "ShellManager.h"

ShellManager::ShellManager()
{
}

ShellManager::~ShellManager()
{
	for (Shell* shell : shells)
	{
		delete shell;
	}
	shells.clear();
}

void ShellManager::Update()
{
	for (Shell* shell : shells)
	{
		shell->Update();
	}
}

void ShellManager::Render(HDC hdc)
{
	for (Shell* shell : shells)
	{
		shell->Render(hdc);
	}
}

Shell* ShellManager::SetShell(Tutle* tutle)
{
	shells.push_back(new Shell(tutle));
	
	return shells.back();
}

void ShellManager::IsCollisionMarioToShell(Mario* mario)
{
	if (mario->GetDie()) return;
	if (mario->GetMode() == 3 || mario->GetMode() == 4) return;

	for (Shell* shell : shells)
	{
		if (shell->IsCollision(mario, overlapSize))
		{
			if (!shell->Attack())
			{
				if (overlapSize.x > overlapSize.y)
				{
					mario->Pos().y -= overlapSize.y;
					mario->PushEnemy();
				}
				shell->Attack() = true;
				shell->SetDirection(shell->Pos() - mario->Pos());
			}
			else if(shell->Attack())
			{
				if (overlapSize.x > overlapSize.y )
				{
					mario->Pos().y -= overlapSize.y;
					mario->PushEnemy();
					shell->Attack() = false;
					shell->Ready() = false;
					Audio::Get()->Play("Kick", 0.7f);
				}
				else
				{
					mario->IsHit();
					Audio::Get()->Play("Kick", 0.7f);
				}
			}
		}
	}
}

void ShellManager::IsCollisionEnemyToShell(Enemy* enemy)
{
	for (Shell* shell : shells)
	{
		if (shell->IsCollision(enemy) && enemy->Active() && shell->Attack())
		{
			enemy->HiddenDeath() = true;
			/*if( WIN_WIDTH > abs(Camera::Get()->GetPos().x - shell->Pos().x))
				Audio::Get()->Play("Kick", 0.7f);*/
			
		}
	}
}
