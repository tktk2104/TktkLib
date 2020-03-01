#pragma once

class RunFuncCheckTest
{
public:

	RunFuncCheckTest(bool printRunFuncLog);

	~RunFuncCheckTest();

public:

	void frameBegin();

	void awake();

	void start();

	bool isActive();

	void onEnable();

	void onDisable();

	void update();

	void afterCollide();

	void draw() const;

	void frameEnd();

	bool isDestroy();

	void onDestroy();

private:

	bool m_printRunFuncLog{ false };

	bool m_isActive{ true };

	bool m_isDestroy{ false };
};