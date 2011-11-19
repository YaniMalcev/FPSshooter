#include "GlobalIncludes.h"
#include "Game.h"
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

Game::Game()
:FPS(25),
TIME_PER_FRAME(1000 / FPS),
FRACTION_TIME_PER_FRAME(TIME_PER_FRAME / 1000.0f){}

void Game::Init(HINSTANCE hInstance){
Init_Window(hInstance);
Init_D3D();
init_input(hWnd);
terrain = new Terrain(d3ddev);
levelmanager= new LevelManager();
GameLevel* level1 = new Level1();
LevelManager::currentLevel = level1;
}

void Game::Init_Window(HINSTANCE hInstance){
	
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Game::WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;   
    wc.lpszClassName = (LPCSTR)L"WindowClass";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL,
						 (LPCSTR)L"WindowClass",
						 (LPCSTR)L"Our Direct3D Program",
                          WS_OVERLAPPEDWINDOW,
						  0,
						  0,
						  SCREEN_WIDTH, SCREEN_HEIGHT,
                          NULL,
						  NULL,
						  hInstance,
						  NULL);

    ShowWindow(hWnd, 1);
}
void Game::Init_D3D(){
	LPDIRECT3D9 d3d;
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = SCREEN_WIDTH;
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
	camera = new Camera();


    D3DLIGHT9 light;    // create the light struct
    ZeroMemory(&light, sizeof(light));    // clear out the light struct for use
    light.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
    light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);    // set the light's color
    light.Direction = D3DXVECTOR3(-1.0f, -1.5f,-1.0f); 

    d3ddev->SetLight(0, &light);    // send the light struct properties to light 
    d3ddev->LightEnable(0, TRUE);    
	

    d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);    // turn off the 3D lighting
    d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);    // turn off culling
    d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
	d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(200, 200, 200)); //set global light
}
void Game::init_input(HWND hWnd)
{
    RAWINPUTDEVICE Mouse;
    Mouse.usUsage = 0x02;    // register mouse
    Mouse.usUsagePage = 0x01;    // top-level mouse
    Mouse.dwFlags = NULL;    // flags
    Mouse.hwndTarget = hWnd;    // handle to a window

    RegisterRawInputDevices(&Mouse, 1, sizeof(RAWINPUTDEVICE));    // register the device
}

void Game::HandleMouse(RAWINPUT InputData){
	static BOOL MouseDown;
	if(InputData.data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_DOWN){
			SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			MouseDown = TRUE;
	}
    if(InputData.data.mouse.usButtonFlags == RI_MOUSE_RIGHT_BUTTON_UP)
        MouseDown = FALSE;


	
	if(MouseDown){
		GetCursorPos(&MousePos);    // get the mouse data
	SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);    // move the mouse to the center
	MousePos.x -= SCREEN_WIDTH / 2;
	MousePos.y -= SCREEN_HEIGHT / 2;
	camera->movingY += MousePos.x * 0.002f;
	camera->movingX -= MousePos.y * 0.002f;
		
	}
	
}

void Game::HandleKeyboard()
{
	D3DXVECTOR3 Direction;

		if( KEY_DOWN(0x57))
			camera->Move(camera->C_LookAtPos - camera->C_Postion);
		if( KEY_DOWN(0x53))
			camera->Move(camera->C_Postion - camera->C_LookAtPos);
		if( KEY_DOWN(0x41)){
			D3DXVec3Cross(&Direction,&(camera->C_LookAtPos - camera->C_Postion),&camera->C_UpVect);
			camera->Move(Direction);
		}
		if( KEY_DOWN(0x44)){
			D3DXVec3Cross(&Direction,&(camera->C_Postion- camera->C_LookAtPos ),&camera->C_UpVect);
			camera->Move(Direction);
		}
	
	if( ::GetAsyncKeyState(VK_ESCAPE) & 0x8000f )
		PostQuitMessage(0);
}
LRESULT CALLBACK Game::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	switch(message)
    {	
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;	
		} break;

		case WM_INPUT:
		{
			RAWINPUT MouceData;
			
			UINT DataSize = sizeof(RAWINPUT);
			GetRawInputData((HRAWINPUT)lParam,
							RID_INPUT,
							&MouceData,
							&DataSize,
							sizeof(RAWINPUTHEADER));
			extern Game game;
			game.HandleMouse(MouceData);		
			
		}break;

		case WM_KEYDOWN:
		{
			extern Game game;
			game.HandleKeyboard();		
		}break;
    }
    return DefWindowProc (hWnd, message, wParam, lParam);
}   
void Game::Run(){
	DWORD lastTime= GetTickCount();
MSG msg;
	while(TRUE)
	{
		 DWORD currentTime = GetTickCount();
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{	
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
			break;
		while( currentTime - lastTime >= TIME_PER_FRAME)
        {
            update();
            lastTime += TIME_PER_FRAME;

        }
		render();		
	}
}

void Game::update(){
	levelmanager->Update();
	camera->Update(d3ddev);
}
void Game::render(){
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	
    d3ddev->BeginScene();


    // set the projection transform
    D3DXMATRIX matProjection;    // the projection transform matrix
    D3DXMatrixPerspectiveFovLH(&matProjection,
                               D3DXToRadian(45),    // the horizontal field of view
                               (FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, // aspect ratio
                               0.01f,   // the near view-plane
                               500.0f);    // the far view-plane
    d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection); // set the projection

	terrain->Draw(d3ddev);
    d3ddev->EndScene(); 

    d3ddev->Present(NULL, NULL, NULL, NULL);

}

void Game::End(){
	delete terrain;
	delete camera;
    d3ddev->Release();
    

}