
/*
 Copyright (c) 2012, The Cinder Project, All rights reserved.

 This code is intended for use with the Cinder C++ library: http://libcinder.org

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and
	the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
	the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once


#include "cinder/app/AppImplLinux.h"
#include "cinder/app/AppImplLinuxRenderer.h"
#include "cinder/Display.h"
#include "cinder/app/Window.h"

namespace cinder { namespace app {

class WindowImplLinuxBasic;

class AppImplLinuxBasic : public AppImplLinux {
  public:
	AppImplLinuxBasic( class AppBasic *aApp  );
	void	run();

	class AppBasic*		getApp() { return mApp; }
	
	void	quit() { std::cout << " ABOUT TO QUIT !! " << std::endl; mShouldQuit = true; }

	float	setFrameRate( float aFrameRate );
	void	disableFrameRate();
	bool	isFrameRateEnabled() const;

	size_t		getNumWindows() const;
	WindowRef	getWindowIndex( size_t index );
	WindowRef	getForegroundWindow() const;
	fs::path	getAppPath() const;
	

  private:
	void		sleep( double seconds );

    void        handleXEvents();

	WindowRef	createWindow( Window::Format format );
	virtual void	closeWindow( class WindowImplLinux *windowImpl ) override;
	virtual void	setForegroundWindow( WindowRef window ) override;
	
	bool		mShouldQuit;
	class AppBasic	*mApp;
	
	double		mNextFrameTime;
	bool		mFrameRateEnabled;

    unsigned int prepModifiers( unsigned int state );
	WindowRef	mForegroundWindow;
	std::list<class WindowImplLinuxBasic*> mWindows;

	friend class AppBasic;
};

class WindowImplLinuxBasic : public WindowImplLinux {
  public:
	WindowImplLinuxBasic( const Window::Format &format, RendererRef sharedRenderer, AppImplLinuxBasic *appImpl )
		: WindowImplLinux( format, sharedRenderer, appImpl ), mAppImplBasic( appImpl ) {}

	virtual void toggleFullScreen( const app::FullScreenOptions &options );

  protected:
	AppImplLinuxBasic		*mAppImplBasic;
	friend AppImplLinuxBasic;
};

} } // namespace cinder::app
