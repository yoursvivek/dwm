void
gaplessgrid(Monitor *m) {
        unsigned int n, cols, rows, cn, rn, i, cx, cy, cw, ch, steps, rw, rh;
        Client *c;
        int wide = (m->ww / m->wh)>1.4;

        for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next))
                n++;
        if(n == 0)
                return;

        /* grid dimensions */
        for(cols = 0; cols <= n/2; cols++)
                if(cols*cols >= n)
                        break;
        if(n == 5) /* set layout against the general calculation: not 1:2:2, but 2:3 */
            steps = 2;

        /* cols are rows and rows are cols */
        //cols = wide ? steps : n/steps;
        //rows = wide ? n/steps : steps;
        //cols =steps;
        rows =n/cols;
        rw = wide ? m->ww : m->wh;
        rh = wide ? m->wh : m->ww;

        /* window geometries */
        cw = cols ? rw / cols : rw;
        cn = 0; /* current column number */
        rn = 0; /* current row number */
        for(i = 0, c = nexttiled(m->clients); c; i++, c = nexttiled(c->next)) {
                if(i/rows + 1 > cols - n%cols)
                        rows = n/cols + 1;
                ch = rows ? rh / rows : rh;
                cx = m->wx + (wide ? cn*cw : rn*ch);
                cy = m->wy + (wide ? rn*ch : cn*cw);
                resize(c, cx, cy, (wide ? cw : ch) - 2 * c->bw, (wide ? ch : cw) - 2 * c->bw, False);
                rn++;
                if(rn >= rows) {
                        rn = 0;
                        cn++;
                }
        }
}

/*void
gaplessgrid(Monitor *m) {
	unsigned int n, cols, rows, cn, rn, i, cx, cy, cw, ch;
	Client *c;

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next))
		n++;
	if(n == 0)
		return;

	// grid dimensions
	for(rows = 0; rows <= n/2; rows++)
		if(rows*rows >= n)
			break;
	if(n == 5) // set layout against the general calculation: not 1:2:2, but 2:3
		rows = 2;
	cols = n/rows;

	// window geometries
	ch = rows ? m->wh / rows : m->wh;
	cn = 0; // current column number
	rn = 0; // current row number
	for(i = 0, c = nexttiled(m->clients); c; i++, c = nexttiled(c->next)) {
		if(i/cols + 1 > rows - n%rows)
			cols = n/rows + 1;
		cw = cols ? m->ww / cols : m->ww;
		cx = m->wx + cn*cw;
		cy = m->wy + rn*ch;
		resize(c, cx, cy, cw - 2 * c->bw, ch - 2 * c->bw, False);
		cn++;
		if(cn >= cols) {
			cn = 0;
			rn++;
		}
	}
}
*/