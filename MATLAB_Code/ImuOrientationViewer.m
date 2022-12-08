classdef ImuOrientationViewer < matlab.System
    % Visualization of IMU orientation.
    % This code is based on MathWorks' HelperPoseViewer
    

    % Public, tunable properties
    properties (Nontunable)
        NumInputs = 1;
        OrientationTitle = {'Orientation - Estimated', 'Orientation - Ground Truth'}
        ReferenceFrame = 'ENU';
    end

    properties (Hidden)
        AppWindow;
    end

    % Pre-computed constants
    properties (Access = private)
        pOrientationViewer = gobjects;
    end

    properties (Access = private, Constant)
        ORIENTATION_VIEWER_POSITION = [0 0 1 1];
        BORDER_HEIGHT = 0.05;
    end

    methods
        % Constructor
        function obj = ImuOrientationViewer(varargin)
            setProperties(obj,nargin,varargin{:});
            createUI(obj);
        end    
        % Destructor
        function delete(obj)
            fig = obj.AppWindow;
            if (~isempty(fig) && ishghandle(fig))
                delete(fig);
            end
        end
        function show(obj)
            fig = obj.AppWindow;
            if (~isempty(fig) && ishghandle(fig))
                fig.Visible = 'on';
            end
        end
        function hide(obj)
            set(obj.AppWindow,'Visible','off');
        end
    end

    methods (Access = protected)

        function setupImpl(obj, varargin)
            % Perform one-time calculations, such as computing constants
            show(obj);
        end

        function stepImpl(obj,varargin)
            % Implement algorithm. Calculate y as a function of input u and
            % discrete states.
            obj.pOrientationViewer.Orientation = varargin{1};
        end

        function createUI(obj)
            createAppWindow(obj);
            createOrientationViewer(obj);
        end

        function createAppWindow(obj)
            fig = figure('Name', 'Imu Orientation Viewer', ...
                'NumberTitle', 'off', ...
                'DockControls','off', ...
                'Units', 'normalized', ...
                'OuterPosition', [0 0 0.25 0.5], ...
                'Visible', 'off', ...
                'HandleVisibility', 'on', ...
                'NextPlot', 'new', ...
                'IntegerHandle', 'off', ...
                'CloseRequestFcn', @(x,~)set(x,'Visible', 'off'));

            obj.AppWindow = fig;
        end


        function resetImpl(obj)
            
        end

        function createOrientationViewer(obj)
            ax = axes(obj.AppWindow, 'OuterPosition', obj.ORIENTATION_VIEWER_POSITION);
            obj.pOrientationViewer = poseplot(ax, obj.ReferenceFrame);
        end

    end
end

