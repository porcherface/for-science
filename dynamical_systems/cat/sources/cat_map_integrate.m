function out = cat_map_integrate(in)

out(:,1) = in(:,1) + in(:,2);
out(:,2) = in(:,1) + 2*in(:,2);

out = out - floor(out);
