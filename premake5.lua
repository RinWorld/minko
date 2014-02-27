newoption {
	trigger	= 'no-example',
	description = 'Disable examples.'
}

newoption {
	trigger	= 'no-test',
	description = 'Disable tests.'
}

newoption {
	trigger = 'dist-dir',
	description = 'Output folder for the redistributable SDK built with the \'dist\' action.'
}

solution "minko"
	MINKO_HOME = path.getabsolute(os.getcwd())
	
	dofile('sdk.lua')

	-- buildable SDK
	MINKO_SDK_DIST = false
	
	include 'framework'
	
	-- plugin
	include 'plugin/lua'
	include 'plugin/angle'
	include 'plugin/assimp'
	include 'plugin/devil'
	include 'plugin/bullet'
	include 'plugin/fx'
	include 'plugin/http-loader'
	include 'plugin/http-worker'
	include 'plugin/jpeg'
	include 'plugin/leap'
	include 'plugin/oculus'
	include 'plugin/offscreen'
	include 'plugin/particles'
	include 'plugin/png'
	include 'plugin/sdl'
	include 'plugin/serializer'
	include 'plugin/webgl'

	-- example
	if not _OPTIONS['no-example'] then
		include 'example/lua-scripts'
		include 'example/assimp'
		include 'example/cube'
		include 'example/devil'
		include 'example/effect-config'
		include 'example/frustum'
		include 'example/jobs'
		include 'example/leap-motion'
		include 'example/light'
		include 'example/line-geometry'
		include 'example/offscreen'
		include 'example/picking'
		include 'example/raycasting'
		include 'example/serializer'
		include 'example/sky-box'
		include 'example/stencil'
		include 'example/visibility'
		include 'example/multi-surfaces'
		include 'example/physics'
		include 'example/oculus'
		include 'example/http'
		include 'example/joystick'
	end

	-- test
	if not _OPTIONS['no-test'] then
		include 'test'
	end

newaction {
	trigger		= 'dist',
	description	= 'Generate the distributable version of the Minko SDK.',
	execute		= function()
	
		print("Building documentation...")
		os.execute("doxygen doc/Doxyfile")

		local distDir = 'dist'
		
		if _OPTIONS['dist-dir'] then
			distDir = _OPTIONS['dist-dir']
		end
		
		os.rmdir(distDir)

		os.mkdir(distDir)
		os.copyfile('sdk.lua', distDir .. '/sdk.lua')

		print("Packaging core framework...")
		
		-- framework
		os.mkdir(distDir .. '/framework')
		os.mkdir(distDir .. '/framework/bin')
		minko.os.copyfiles('framework/bin', distDir .. '/framework/bin')
		os.mkdir(distDir .. '/framework/include')
		minko.os.copyfiles('framework/include', distDir .. '/framework/include')
		os.mkdir(distDir .. '/framework/lib')
		minko.os.copyfiles('framework/lib', distDir .. '/framework/lib')
		os.mkdir(distDir .. '/framework/asset')
		minko.os.copyfiles('framework/asset', distDir .. '/framework/asset')

		-- skeleton
		os.mkdir(distDir .. '/skeleton')
		minko.os.copyfiles('skeleton', distDir .. '/skeleton')
		
		-- module
		os.mkdir(distDir .. '/module')
		minko.os.copyfiles('module', distDir .. '/module')
		
		-- -- doc
		-- os.mkdir(distDir .. '/doc')
		-- minko.os.copyfiles('doc/html', distDir .. '/doc')
		
		-- tool
		os.mkdir(distDir .. '/tool/')
		minko.os.copyfiles('tool', distDir .. '/tool')
		
		-- plugin
		local plugins = os.matchdirs('plugin/*')

		os.mkdir(distDir .. '/plugin')
		for i, basedir in ipairs(plugins) do
			local pluginName = path.getbasename(basedir)

			print('Packaging plugin "' .. pluginName .. '"...')

			-- plugins
			local dir = distDir .. '/plugin/' .. path.getbasename(basedir)
			local binDir = dir .. '/bin'

			-- plugin.lua
			assert(os.isfile(basedir .. '/plugin.lua'), 'missing plugin.lua')			
			os.mkdir(dir)
			os.copyfile(basedir .. '/plugin.lua', dir .. '/plugin.lua')

			if minko.plugin[pluginName] and minko.plugin[pluginName].dist then
				minko.plugin[pluginName]:dist(dir)
			end

			-- bin
			if os.isdir(basedir .. '/bin') then
				os.mkdir(binDir)
				minko.os.copyfiles(basedir .. '/bin', binDir)
			end

			-- includes
			if os.isdir(basedir .. '/include') then
				os.mkdir(dir .. '/include')
				minko.os.copyfiles(basedir .. '/include', dir .. '/include')
			end
			
			-- assets
			if os.isdir(basedir .. '/asset') then
				os.mkdir(dir .. '/asset')
				minko.os.copyfiles(basedir .. '/asset', dir .. '/asset')
			end
		end

		minko.action.zip(distDir, distDir .. '.zip')
	end
}

newaction {
	trigger			= "doc",
	description		= "Create developer reference.",
	execute			= function()
		os.execute("doxygen doc/Doxyfile")
	end
}

newaction {
	trigger			= "clean",
	description		= "Remove generated files.",
	execute			= function()
		minko.action.clean()
	end
}
