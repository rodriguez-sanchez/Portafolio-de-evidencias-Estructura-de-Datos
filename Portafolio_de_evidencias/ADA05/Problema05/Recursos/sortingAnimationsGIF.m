simultaneousSortingGIF()

function simultaneousSortingGIF()
    % Parámetros
    n = 100;
    delay_time = 0.05;
    arr_original = randperm(n);
    
    % Copias para cada algoritmo
    arr_ins = arr_original;
    arr_shell = arr_original;
    arr_hibbard = arr_original;
    
    % Variables para Insertion Sort
    i_ins = 2;
    j_ins = i_ins - 1;
    key_ins = arr_ins(i_ins);
    ins_done = false;
    
    % Variables para Shell Sort clásico
    gap_shell = floor(n/2);
    i_shell = gap_shell + 1;
    j_shell = i_shell;
    temp_shell = arr_shell(i_shell);
    shell_done = false;
    in_shell_inner = false;
    
    % Variables para Shell Sort Hibbard
    % Generar incrementos Hibbard
    h = [];
    k = 1;
    while true
        g = 2^k - 1;
        if g > n
            break;
        end
        h = [g h]; % decreciente
        k = k + 1;
    end
    hibbard_idx = 1;
    gap_hibbard = h(hibbard_idx);
    i_hibbard = gap_hibbard + 1;
    j_hibbard = i_hibbard;
    temp_hibbard = arr_hibbard(i_hibbard);
    hibbard_done = false;
    in_hibbard_inner = false;
    
    % Preparar figura
    fig = figure('Name', 'Simultaneous Sorting', 'NumberTitle', 'off');
    axis([1 n 0 n]);
    xlabel('Índice');
    ylabel('Valor');
    
    % Mostrar ticks cada 10 para no saturar
    xticks(1:10:n);
    yticks(0:10:n);
    grid on;
    
    filename = 'simultaneous_sorting.gif';
    persistent firstFrameWritten
    firstFrameWritten = false;
    
    % Ciclo hasta que los 3 terminen
    while ~(ins_done && shell_done && hibbard_done)
        % --- Un paso de Insertion Sort ---
        if ~ins_done
            if j_ins >= 1 && arr_ins(j_ins) > key_ins
                arr_ins(j_ins + 1) = arr_ins(j_ins);
                j_ins = j_ins - 1;
            else
                arr_ins(j_ins + 1) = key_ins;
                i_ins = i_ins + 1;
                if i_ins > n
                    ins_done = true;
                else
                    key_ins = arr_ins(i_ins);
                    j_ins = i_ins - 1;
                end
            end
        end
        
        % --- Un paso de Shell Sort clásico ---
        if ~shell_done
            if ~in_shell_inner
                if i_shell <= n
                    temp_shell = arr_shell(i_shell);
                    j_shell = i_shell;
                    in_shell_inner = true;
                else
                    gap_shell = floor(gap_shell/2);
                    if gap_shell == 0
                        shell_done = true;
                    else
                        i_shell = gap_shell + 1;
                    end
                end
            else
                if j_shell > gap_shell && arr_shell(j_shell - gap_shell) > temp_shell
                    arr_shell(j_shell) = arr_shell(j_shell - gap_shell);
                    j_shell = j_shell - gap_shell;
                else
                    arr_shell(j_shell) = temp_shell;
                    i_shell = i_shell + 1;
                    in_shell_inner = false;
                end
            end
        end
        
        % --- Un paso de Shell Sort Hibbard ---
        if ~hibbard_done
            if ~in_hibbard_inner
                if i_hibbard <= n
                    temp_hibbard = arr_hibbard(i_hibbard);
                    j_hibbard = i_hibbard;
                    in_hibbard_inner = true;
                else
                    hibbard_idx = hibbard_idx + 1;
                    if hibbard_idx > length(h)
                        hibbard_done = true;
                    else
                        gap_hibbard = h(hibbard_idx);
                        i_hibbard = gap_hibbard + 1;
                    end
                end
            else
                if j_hibbard > gap_hibbard && arr_hibbard(j_hibbard - gap_hibbard) > temp_hibbard
                    arr_hibbard(j_hibbard) = arr_hibbard(j_hibbard - gap_hibbard);
                    j_hibbard = j_hibbard - gap_hibbard;
                else
                    arr_hibbard(j_hibbard) = temp_hibbard;
                    i_hibbard = i_hibbard + 1;
                    in_hibbard_inner = false;
                end
            end
        end
        
        % Dibujar los 3 arreglos
        cla;
        hold on;
        plot(arr_ins, 'o-', 'Color', 'b', 'MarkerEdgeColor', 'b', 'MarkerFaceColor', 'b', 'MarkerSize', 5, 'LineWidth', 1.5);
        plot(arr_shell, 'o-', 'Color', 'm', 'MarkerEdgeColor', 'm', 'MarkerFaceColor', 'm', 'MarkerSize', 5, 'LineWidth', 1.5);
        plot(arr_hibbard, 'o-', 'Color', 'r', 'MarkerEdgeColor', 'r', 'MarkerFaceColor', 'r', 'MarkerSize', 5, 'LineWidth', 1.5);
        hold off;
        drawnow;
        
        % Capturar frame para GIF
        frame = getframe(fig);
        im = frame2im(frame);
        [imind, cm] = rgb2ind(im, 256);
        if ~firstFrameWritten
            imwrite(imind, cm, filename, 'gif', 'Loopcount', inf, 'DelayTime', delay_time);
            firstFrameWritten = true;
        else
            imwrite(imind, cm, filename, 'gif', 'WriteMode', 'append', 'DelayTime', delay_time);
        end
    end
    
    close(fig);
    disp(['GIF guardado en: ', filename]);
end
