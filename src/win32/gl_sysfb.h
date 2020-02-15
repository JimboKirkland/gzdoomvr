#ifndef __WIN32_GL_SYSFB_H__
#define __WIN32_GL_SYSFB_H__

#include "v_video.h"

class SystemGLFrameBuffer : public DFrameBuffer
{
	typedef DFrameBuffer Super;

	void SaveWindowedPos();
	void RestoreWindowedPos();

public:
	SystemGLFrameBuffer() {}
	// Actually, hMonitor is a HMONITOR, but it's passed as a void * as there
    // look to be some cross-platform bits in the way.
	SystemGLFrameBuffer(void *hMonitor, bool fullscreen);
	virtual ~SystemGLFrameBuffer();

	void SetVSync (bool vsync);
	void SwapBuffers();

	int GetClientWidth() override;
	int GetClientHeight() override;

	bool IsFullscreen() override;
	void ToggleFullscreen(bool yes) override;

	void InitializeState();

protected:

	void GetCenteredPos(int in_w, int in_h, int &winx, int &winy, int &winw, int &winh, int &scrwidth, int &scrheight);
	void KeepWindowOnScreen(int &winx, int &winy, int winw, int winh, int scrwidth, int scrheight);

	void PositionWindow(bool fullscreen);

	void ResetGammaTable();
	void SetGammaTable(uint16_t * tbl);

	float m_Gamma, m_Brightness, m_Contrast;
	uint16_t m_origGamma[768];
	bool m_supportsGamma;
	bool m_Fullscreen;
	char m_displayDeviceNameBuffer[32/*CCHDEVICENAME*/];	// do not use windows.h constants here!
	char *m_displayDeviceName;
	void *m_Monitor;
	int SwapInterval;

	friend class Win32GLVideo;

};

#endif // __WIN32_GL_SYSFB_H__
